#include "interpolate.h"
#include <stdio.h>
#include <stdlib.h>
extern word_t _storage[PHYSICAL_SIZE];

//	optimized kernel for assembly
//	perform load-and-interpolate
word_t __fastcall read_quadratic(address_t address) {
	register dword_t value, b, c,value1;
	register aword_t z0, z1, z0_by_z1;
	register word_t	y0, y1, y2;
	register address_t x0, x1, x2,temp1,temp2,temp3,temp4,temp5,temp6;
	signed short temp7;
	//	keep address in bounds
	address &= LOGICAL_BITMASK; //LOGICAL_BITMASK=(LOGICAL_SIZE - 1)=5111

	//	compute indices
	temp1 = (address - RESOLUTION_BY_2);//complement
	temp2 = (address - RESOLUTION_BY_2) >> RESOLUTION_LOG2;
	temp3 = temp1 >> RESOLUTION_LOG2;
	//                8                     4               11111
	x0 = ((address - RESOLUTION_BY_2) >> RESOLUTION_LOG2) & PHYSICAL_BITMASK;
	x1 = (x0 + 1) & PHYSICAL_BITMASK;//31
	x2 = (x0 + 2) & PHYSICAL_BITMASK;//31

	//	compute shifts                                      1000
	temp4 = (address & RESOLUTION_BITMASK);//15
	temp5 = ((~address) & RESOLUTION_BY_2_MSB);//0 or 8
	//temp6 = (((~address) & RESOLUTION_BY_2_MSB) << 1);//0 or 16
	//temp7 = (~address);
	z0 = (address & RESOLUTION_BITMASK) | (((~address) & RESOLUTION_BY_2_MSB) << 1);
	z1 = z0 - RESOLUTION; //16
	z0_by_z1 = z0 * z1;

	//printf("address=%d,temp6=%d,z0=%d,z1=%d\n", address, temp6,z0,z1);
	//printf("%d,",  (address & RESOLUTION_BITMASK));
	//printf("%d,", temp6);
	//printf("%d,",  z0);

	//	load three data elements
	y0 = _storage[x0];
	y1 = _storage[x1];
	y2 = _storage[x2];
	
	//	compute polynomial weights in full precision
	b = y1 - y0; 
	c = y2 - (b << 1) - y0;

	//	evaluate polynomial in full precision and add roundoff
	value = (y0 << TWO_RESOLUTION_SQUARE_LOG2)//9
			+ ((b * z0) << TWO_RESOLUTION_LOG2)//5
			+ c * z0_by_z1
			+ ROUNDOFF;//0,0111,1111
	temp6 = (y0 << TWO_RESOLUTION_SQUARE_LOG2);
	temp7 = ((b * z0) << TWO_RESOLUTION_LOG2)+ (y0 << TWO_RESOLUTION_SQUARE_LOG2);

 	value1= value >> TWO_RESOLUTION_SQUARE_LOG2;//9
	//	scale back to output precision
	return value >> TWO_RESOLUTION_SQUARE_LOG2;
}
