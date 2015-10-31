/* 
 * File:   mem_segments.cpp
 * Author: thanhpv
 * About segments in memory of a process
 * Created on October 31, 2015, 3:57 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*
 * 
 */
char globalBuf[365]; /*Uninitialized data segment*/
int prime[] = {1, 2, 3, 4}; /*Initialized data segment*/

static int
square(int x) /*Allocated in frame for square*/ {
	int result; /*Allocated in frame for square*/
	result = x*x;
	return result; /*Return value passed via register*/
}

int main(int argc, char** argv) { /*Allocated in frame for main*/
	static int key = 100; /*Initialized data segment*/

	static char mbuf[200]; /*Uninitialized data segment*/

	char *p; /*Allocated in frame for main*/

	p = (char*) malloc(1024); /*Points to memory in heap segments*/
	free(p);

	return 0;
}

