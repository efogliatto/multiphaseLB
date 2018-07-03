#include <timeToIndex.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


uint timeToIndex( uint current ) {

    
    uint idx = 0;


    FILE *outFile;

    uint ns = 0;

    


    // Try to open .case file to get time steps

    outFile = fopen("lbm.case", "r");


    if( outFile ) {


	// Read Number of steps

	char word[256];

	uint find = 0;

	uint status;
	    
	while(   ( fscanf(outFile, "%s", word) != EOF )   &&   ( find == 0 )   ) {

	    if( strcmp(word, "number") == 0 ) {

		status = fscanf(outFile, "%s", word);

		if(   ( status != EOF )   &&   ( strcmp(word, "of") == 0 ) ) {

		    status = fscanf(outFile, "%s", word);

		    if(   ( status != EOF )   &&   ( strcmp(word, "steps:") == 0 ) ) {
			    
			status = fscanf(outFile, "%s", word);

			ns = atoi( word );

			find = 1;
			
		    }			
			
		}

	    }

	}




	// Read Time list

	rewind( outFile );
	    
	while(   ( fscanf(outFile, "%s", word) != EOF )   ) {

	    if( strcmp(word, "time") == 0 ) {

		status = fscanf(outFile, "%s", word);

		if(   ( status != EOF )   &&   ( strcmp(word, "values:") == 0 ) ) {

		    uint k;

		    for( k = 0 ; k < ns ; k++ ) {

			status = fscanf(outFile, "%s", word);

			if( current == atoi( word ) ) {

			    idx = k;

			}

		    }
			
		}

	    }

	}
	    


	fclose(outFile);

    }



    

    return idx;

}
