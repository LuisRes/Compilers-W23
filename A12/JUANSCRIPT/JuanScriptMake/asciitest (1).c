#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXNUMCHARS 1000
#define VALIDRANGE 128
#define MAXCHARVAL 256

FILE *fd;

void seqTest() {
	int i;
	for (i=0; i<MAXCHARVAL; i++) {
		fprintf(fd, "%c",i);
	}
}

void randTest() {
	int i, r;
	for (i=0; i<MAXNUMCHARS; i++) {
		r = rand() % MAXCHARVAL;
		fprintf(fd, "%c",r);		
	}
}

int main() {
	char adress[] = "D:\JUANSCRIPT\JuanScriptMake\out\build\x64-debug\charTest.txt";
	fd = fopen(adress, "wt");
	
	fprintf(fd, "Sequential Chars.....................\n");
	seqTest();
	fprintf(fd, "\nRandom Chars.........................\n");
	randTest();
	return 0;
}

