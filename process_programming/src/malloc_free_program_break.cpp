/* 
 * File:   malloc_free_program_break.cpp
 * Author: thanhpv
 *
 * Created on November 1, 2015, 1:04 AM
 */

#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#define MAX_ALLOCS 1000000
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
	//	printf("Program break is: %10p\n", sbrk(0));/*Program break is:  0x1f17000*/ 32600064
	//	char* ptr;
	//	ptr = (char*)malloc(200);
	//	printf("Program break after malloc is: %10p\n", sbrk(0));/*Program break after malloc is:  0x1f38000*/ 32735232
	//	free(ptr);
	//	printf("Program break after free is: %10p\n", sbrk(0));/*Program break after free is:  0x1f38000*/

	char* ptr[MAX_ALLOCS];
	int freeStep, freeMin, freeMax, blocksize, numAllocs, j;

	printf("\n");

	numAllocs = atoi(argv[1]);
	if (numAllocs > MAX_ALLOCS) {
		printf("Num allocs must lower than MAX_ALLOCS: \n");
		exit(-1);
	}

	blocksize = atoi(argv[2]);
	freeStep = (argc > 3) ? atoi(argv[3]) : 1;
	freeMin = (argc > 4) ? atoi(argv[4]) : 1;
	freeMax = (argc > 5) ? atoi(argv[5]) : numAllocs;

	if (freeMax > numAllocs) {
		printf("Free Max > num allocs\n");
		exit(-1);
	}

	printf("Inital break: %10p\n", sbrk(0));
	printf("Allocated %d*%d bytes\n", numAllocs, blocksize);

	for (j = 0; j < numAllocs; j++) {
		ptr[j] = (char*) malloc(blocksize);
		if (ptr[j] == NULL) {
			printf("Cann't malloc more %d\n", j);
			exit(-1);
		}
	}
	printf("Program break after malloc: %10p\n", sbrk(0));
	printf("Free blocks from %d to %d in steps of %d\n",
			freeMin, freeMax, freeStep);
	for (j = freeMin - 1; j < freeMax; j += freeStep) {
		free(ptr[j]);
	}
	printf("After free(), program break is: %10p\n", sbrk(0));
	return 0;
}

//[thanhpv@ThinkPad-T450:bin] $ ./process_programming 1000 1024 2

//Inital break:  0x166c000
//Allocated 1000*1024 bytes
//Program break after malloc:  0x1774000
//Free blocks from 1 to 1000 in steps of 2
//After free(), program break is:  0x1774000


//[thanhpv@ThinkPad-T450:bin] $ ./process_programming 1000 1024 1 1 999

//Inital break:   0xa5b000 = 10858496
//Allocated 1000*1024 bytes
//Program break after malloc:   0xb63000 = 11939840
//Free blocks from 1 to 999 in steps of 1 
//After free(), program break is:   0xb63000

//If free at top of heap, free will use sbrk to decrease heap size
//[thanhpv@ThinkPad-T450:bin] $ ./process_programming 1000 1024 1 500 1000

//Inital break:  0x256d000
//Allocated 1000*1024 bytes
//Program break after malloc:  0x2675000
//Free blocks from 500 to 1000 in steps of 1
//After free(), program break is:  0x260c000


//[thanhpv@ThinkPad-T450:bin] $ ./process_programming 1000 1024 1 990 1000
//
//Inital break:   0x6ef000
//Allocated 1000*1024 bytes
//Program break after malloc:   0x7f7000
//Free blocks from 990 to 1000 in steps of 1
//After free(), program break is:   0x7f7000


//VUNG HEAP KO LIEN TUC => (END - BEGIN) /1024 <> 1000