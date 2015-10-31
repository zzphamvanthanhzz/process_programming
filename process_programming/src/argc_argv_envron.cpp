/* 
 * File:   argc_argv_envron.cpp
 * Author: thanhpv
 * About argc, argv, environ
 * Created on November 1, 2015, 12:20 AM
 */

#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
	printf("Number of argument is: %d\n", argc);
	char** p;
	for (p = argv; *p != NULL; p++) {
		printf("%s\n", *p);
	}

	printf("Environment\n");
	char** e;
	for (e = environ; *e != NULL; e++) {
		printf("%s\n", *e);
	}
	return 0;
}

