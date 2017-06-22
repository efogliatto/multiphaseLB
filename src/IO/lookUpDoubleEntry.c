/* #include <lookUpDoubleEntry.h> */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double lookUpDoubleEntry( char* filename, char* entry, double df ) {

    // Open file
    FILE *fp;
    fp = fopen(filename,"r");

    if(fp == NULL) {

	printf("\n [ERROR]   Unable to open file %s\n\n", filename);

	exit(0);

    }



    // Move over file and check for entry
    char re[100];
    double aux;
    
    while( fscanf(fp,"%s",re) == 1 ) {
	
	if (strcmp(entry,re) == 0) {

	    
	    if(fscanf(fp,"%lf",&aux) != 0) {

	    	df = aux;

	    }
	    
	}
	
    }
    

    

    // Close file
    fclose(fp);

    return df;
}
