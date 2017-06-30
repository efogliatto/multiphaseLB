/*

  Return list from file

  Tokenizes entry and returns elements as string

 */


#include <tokenize.h>
#include <entryList.h>
#include <subEntryList.h>
#include <singleEntryList.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenize.h>


typedef unsigned int uint;


unsigned int lookUpEntry( char* fileName, char* entry, char list[][100], unsigned int* lsize ) {


    unsigned int retval = 0;
    

    
    // Tokenize entry string

    uint ntk = 0;
    
    char tok[10][100];


    // Clear tok string
    
    {
    	uint ii,jj;

    	for(ii = 0 ; ii < 10 ; ii++ ) {

	    for(jj = 0 ; jj < 100 ; jj++ ) {

		tok[ii][jj] = '\0';

	    }

    	}
	        
    }


    tokenize(entry, '/', tok, &ntk);


      


    char elist[100][100];

    char subEntry[100][100];

    uint elistSize,
	status,
	nl;    

    
    if( ntk > 1 ) {


    	// Search first entry in file

    	status = entryList(fileName, tok[0], elist, &elistSize);

	

	if (status) {

	    
	    if ( ntk == 2 ) {

		status = singleEntryList( elist, elistSize, tok[1], list, &nl );	       

		if (status) {

		    *lsize = nl;
		    
		    retval = 1;

		}

	    }


	    
	    // Search in intermediate lists
	
	    else {

	
		uint i,
		    nsub;

		for( i = 1 ; i < (ntk-1) ; i++ ) {

		    if( i == 1) {

			status = subEntryList( elist, elistSize, tok[i], subEntry, &nsub );

		    }

		    else {

			status = subEntryList( subEntry, nsub, tok[i], subEntry, &nsub );

		    }

		}




		// Search in last entry

		status = singleEntryList( subEntry, nsub, tok[ntk-1], list, &nl );

		if (status) {

		    *lsize = nl;

		    retval = 1;

		}



	    
	    }



	}

    }




    // Single entry (not tokenized)
    
    else   {

    	uint ne;

	status = entryList(fileName, entry, list, &ne);

	if (status) {
	
	    *lsize = ne;

	    retval = 1;

	}

    }

	
    

    return retval;
    

}
