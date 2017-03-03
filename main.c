//	1D Circular Interpolating Memory Example

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES 
#include <math.h>

//	memory parameters
#include "interpolate.h"

//#define RANDOM
#define TRIGONOMETRIC

//#define	LINEAR_INTERPOLATION
//#define	QUADRATIC_INTERPOLATION
#define		CUBIC_INTERPOLATION

word_t _storage[PHYSICAL_SIZE];

//	memory data structure
typedef struct {
	int logical_size, 
		physical_size,
		resolution;
	word_t *storage;
} imem_t;

//	initialization function
void init_mem(imem_t *memory) {
	int i;
	memory->logical_size = LOGICAL_SIZE;		//512
	memory->physical_size = PHYSICAL_SIZE;		//32
	memory->resolution = LOGICAL_SIZE/PHYSICAL_SIZE; //16
	memory->storage = _storage;
	for (i=0; i<PHYSICAL_SIZE; i++)
		memory->storage[i] = 0;
}

//	load entire memory from DRAM
void load_mem(imem_t *memory, word_t* data) {
	int i;
	for (i=0; i<PHYSICAL_SIZE; i++)
		memory->storage[i] = data[i];
}


//	read a word from logical address
word_t read_mem(imem_t *memory, int address) {
#ifdef LINEAR_INTERPOLATION
	return read_linear(address);
#endif
#ifdef QUADRATIC_INTERPOLATION
	return read_quadratic(address);
#endif
#ifdef CUBIC_INTERPOLATION
	return read_cubic(address);
#endif
		
}


//	driver
int main(void) {
	int i;
	imem_t imem;
	word_t dram[PHYSICAL_SIZE]; //PHYSICAL_SIZE=2^5=32
	
	//	set up memory structure
	init_mem(&imem);

	//	create data in DRAM
	for (i=0; i<PHYSICAL_SIZE; i++) 
	{
		#ifdef TRIGONOMETRIC
			dram[i] = sin((2* M_PI*i)/((double)PHYSICAL_SIZE)) * DYNAMIC_RANGE; //DYNAMIC_RANGE=2^15=32768=32k
		#endif
		#ifdef RANDOM
			dram[i] = rand();
		#endif
		//printf("dram[%d] = %d\n", i, dram[i]);
	    printf("%d\n", dram[i]);
	}

	//	load DRAM data into memory
	load_mem(&imem, dram); 
	printf("\n");

	//	read out interpolating memory
	for (i = 0; i < LOGICAL_SIZE; i++)
	{
		read_mem(&imem, i);
		//printf("imem[%d] =\t%d\n", i, read_mem(&imem, i));
		//printf("%d,", read_mem(&imem, i));
	}

}