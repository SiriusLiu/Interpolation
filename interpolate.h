#ifndef __INTERPOLATE_H__
#define __INTERPOLATE_H__

//	memory parameters
#define PHYSICAL_SIZE_LOG2			(5)
#define RESOLUTION_LOG2				(4)
#define DYNAMIC_RANGE				(1<<15) //32768,32k

//	derived constants
//	shift constants
#define LOGICAL_SIZE_LOG2			(PHYSICAL_SIZE_LOG2 + RESOLUTION_LOG2) //9
#define TWO_RESOLUTION_SQUARE_LOG2	(2 * RESOLUTION_LOG2 + 1) //9
#define TWO_RESOLUTION_LOG2			(RESOLUTION_LOG2 + 1)
#define TWO_RESOLUTION	            (2 * RESOLUTION_LOG2)//8

//	size constants
#define PHYSICAL_SIZE				(1 << PHYSICAL_SIZE_LOG2)	//2^5=32
#define LOGICAL_SIZE				(1 << LOGICAL_SIZE_LOG2)	//2^9=512
#define RESOLUTION					(1 << RESOLUTION_LOG2)      //2^4=16
#define	RESOLUTION_BY_2				(RESOLUTION >> 1)
#define	ROUNDOFF					(((1 << TWO_RESOLUTION_SQUARE_LOG2)- 1) >> 1)

//	bit masks
#define	LOGICAL_BITMASK				(LOGICAL_SIZE - 1)
#define	PHYSICAL_BITMASK			(PHYSICAL_SIZE - 1)
#define	RESOLUTION_BITMASK			(RESOLUTION - 1)
#define RESOLUTION_BY_2_MSB			(1 << (RESOLUTION_LOG2 - 1))
// Cubic Constant
#define P1 (1 << RESOLUTION_LOG2)//16
#define P2 (2 << RESOLUTION_LOG2)//32
#define P3 (3<<RESOLUTION_LOG2)//48


//	C types
typedef signed int word_t;
typedef signed long dword_t;
typedef unsigned short address_t;
typedef signed short aword_t;


//	function prototypes
word_t __fastcall read_linear(address_t address);
word_t __fastcall read_quadratic(address_t address);
word_t __fastcall read_cubic(address_t address);
#endif
