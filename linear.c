#include "interpolate.h"

extern word_t _storage[PHYSICAL_SIZE];

//	optimized kernel for assembly
//	perform load-and-interpolate
word_t __fastcall read_linear(address_t address) 
{
	register word_t rvalue, left_val, right_val;
	register dword_t value, slope,value1;
	register address_t left, right; //typedef unsigned short address_t;
	register aword_t subaddress;
	
	//	keep address in bounds
	address &= (LOGICAL_SIZE - 1);//LOGICAL_SIZE=512

	//	find left and right address and location between
	left = address >> RESOLUTION_LOG2;	        //RESOLUTION_LOG2=4
    right = (left + 1) & (PHYSICAL_SIZE - 1);	//PHYSICAL_SIZE=32
	subaddress = address & (RESOLUTION - 1);	//RESOLUTION=16

	//	get values from storage
	left_val = _storage[left];
	right_val = _storage[right];

	//	compute slope in full precision
	slope = right_val - left_val;

	//	compute interpolated value in high precision
	value = (left_val << RESOLUTION_LOG2) + subaddress * slope; //RESOLUTION_LOG2=4
	value1 = value >> RESOLUTION_LOG2; //divided by 16
	//	scale result back to word_t resolution 
	return value >> RESOLUTION_LOG2;
}
