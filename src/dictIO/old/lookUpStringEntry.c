#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lookUpStringEntry( char* filename, char* entry, char* val ) {

    // Open file
    FILE *fp;
    fp = fopen(filename,"r");

    if(fp == NULL) {

	printf("\n [ERROR]   Unable to open file %s\n\n", filename);

	exit(0);

    }



    // Move over file and check for entry
    char re[100];
    char *dest = NULL;

    // Read while valid
    while( fscanf(fp,"%s",re) == 1 ) {

	// Compare with entry. Read if true
	if (strcmp(entry,re) == 0) {

	    // Read next entry
	    if( fscanf(fp,"%s",re) == 1 ) {

		// Check for token
		if(strstr(re,";") != NULL) {

		    // Tokenize
		    dest = strtok(re,";");

		    // Copy to val
		    strcpy(val,dest);
		    
		}
		
	    }
	    
	}
	
    }
    

    

    // Close file
    fclose(fp);

}
