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

    // Read while valid
    while( fscanf(fp,"%s",re) == 1 ) {

	// Compare with entry. Read if true
	if (strcmp(entry,re) == 0) {

	    // Read next entry
	    if( fscanf(fp,"%s",re) == 1 ) {

		// Check for token
		if(strstr(re,";") != NULL) {

		    // Tokenize
		    char *token = strtok(re,";");

		    // Convert to double
		    char *ptr;
		    df = strtod(token,&ptr);		    
		    
		}
		
	    }
	    
	}
	
    }
    

    

    // Close file
    fclose(fp);

    return df;
}
