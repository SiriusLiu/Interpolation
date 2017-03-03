#include "interpolate.h"
#include <stdio.h>
#include <stdlib.h>
extern word_t _storage[PHYSICAL_SIZE];

//	optimized kernel for assembly
//	perform load-and-interpolate
word_t __fastcall read_cubic(address_t address) {
	register dword_t value, b1,b2,b3, value1,value2,value3;
	//register aword_t z0, z1, z0_by_z1;//short 16bit for a 32bit cpu.
	register word_t z0, z1,z2,z3,k;
	register word_t c1,c2,c3;
	register word_t	y0, y1, y2, y3;
	register address_t xt,x0, x1, x2, x3, x4,temp1, temp2, temp3, temp4, temp5, temp6;
	signed short temp7;
	//	keep address in bounds
	address &= LOGICAL_BITMASK; //LOGICAL_BITMASK=(LOGICAL_SIZE - 1)=5111
	//      8                     4               11111
	x0 = ((address) >> RESOLUTION_LOG2) & PHYSICAL_BITMASK;
	//x0 = (address) & PHYSICAL_BITMASK;
	//x0 = (xt + 1)& PHYSICAL_BITMASK;
	x1 = (x0 + 1) & PHYSICAL_BITMASK;//31
	x2 = (x0 + 2) & PHYSICAL_BITMASK;//31
	x3 = (x0 + 3) & PHYSICAL_BITMASK;//31
	//printf("x0=%d,\t x1=%d,\t x2=%d,\t x3=%d\n", x0, x1, x2, x3);
	y0 = _storage[x0];
	y1 = _storage[x1];
	y2 = _storage[x2];
	y3 = _storage[x3];
	//printf("y0=%d,\t y1=%d,\t y2=%d,\t y3=%d\n", y0, y1, y2, y3);
	z0 = (address & RESOLUTION_BITMASK);
	z1 = z0-P1;
	z2 = z0-P2;
	z3 = z0-P3;
	//printf("z0=%d,\t z1=%d,\t z2=%d,\t z3=%d\n", z0, z1, z2, z3);
	//Suppose k=z0/16
	//c1 = (k - 2)*(k - 3);
	b1 = y1 - y0;
	b2 = y1 - y2;
	b3 = y3 - y2;
	/*value1 = y0*c1*16 + b1*c1*z0
	+y1*c2*16 - b2*c2*z1
	+y2*c3*16 + b3*c3*z2;
	*/
	//value1 = (b1*z0+16*y0)*z2*z3 + (b2*z1-16*y1) *2*z0*z3 + (b3*z2+16*y2)*z0*z1;
	value1 = (b1*z0 + 16 * y0)*z2*z3;
	value2 = (b2*z1 - 16 * y1) * 2 * z0*z3;
	value3=(b3*z2 + 16 * y2)*z0*z1;
	
	value = ((value1+value2+value3) >> 12);
	printf("address=%d,value1=%d\t,value2=%d\t,value3=%d\t,value=%d\n", address,value1,value2,value3,value);
	return value;
}



//value1= (y0<<TWO_RESOLUTION)*c1+
/*value1 = y0*c1*16 + b1*c1*z0
+y1*c2*16 - b2*c2*z1
+y2*c3*16 + b3*c3*z2;
*/

//value1 = (b1*z0 + 16 * y0)*z2*z3+(b2*z1-16*y1)*2*z0*z3+(b2*z2+y2*16)*z0*z1;
//value1 = y0*z1*z2*z3+3*y1*z0*z2*z3-3*y2*z0*z1*z3+y3*z0*z1*z2;
//value1 = -y0*(z0 - 16)*(z0 - 32)*(z0 - 48) + 3 * y1*z0*(z0 - 32)*(z0 - 48) +
//	-3 * y2*z0*(z0 - 16)*(z0 - 48) + y3*z0*(z0 - 16)*(z0 - 32);
//value1 = -y0*z1*z2*z3 + 3 * y1*z0*z2*z3 +
//	    -3 * y2*z0*z1*z3 + y3*z0*z1*z2;
//value1 = (-y0*z1+ y1*z0)*z2*z3 + (y1*z2 - z1*y2)*2*z0*z3 + (y3*z2-y2*z3)*z0*z1;