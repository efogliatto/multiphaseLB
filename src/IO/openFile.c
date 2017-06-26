#include <stdio.h>
#include <stdlib.h>

void openFile( FILE* fp, char* fileName, char* mode) {

    fp = fopen(fileName,mode);

    if(fp == NULL) {

	printf("\n [ERROR]   Unable to open file %s\n\n", fileName);

	exit(1);

    }

}
