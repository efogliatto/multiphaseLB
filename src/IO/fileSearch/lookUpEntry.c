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

typedef unsigned int uint;


char** lookUpEntry( char* fileName, char* entry, unsigned int* lsize ) {

    
    
    // Tokenize entry string

    uint ntk;

    char** tok = tokenize(entry,'/', &ntk);


    uint nl;
    
    char** list;

    

    // Use only for tokenized entries (up to now...)
    
    if( ntk > 1 ) {


    	// Search first entry in file
	
    	uint ne, ii;

    	char** elist = entryList(fileName, tok[0], &ne);

	

    	if ( ntk == 2 ) {

    	    list = singleEntryList( elist, tok[1], &nl, ne );

    	    *lsize = nl;

    	}


    	// Search in intermediate lists
	
    	else {

	
    	    uint i,
    		nsub;

    	    char** subEntry;

    	    for( i = 1 ; i < (ntk-1) ; i++ ) {

    		if( i == 1) {

    		    subEntry = subEntryList( elist, tok[i], &nsub, ne );

    		}

    		else {

    		    subEntry = subEntryList( subEntry, tok[i], &nsub, nsub );

    		}

    	    }




    	    // Search in last entry
    	    list = singleEntryList( subEntry, tok[ntk-1], &nl, nsub );

    	    *lsize = nl;
	    
    	}

	



	// Deallocate arrays

	for(ii = 0 ; ii < ne ; ii++) {

	    free( elist[ii] );
	    
	}
	
	free(elist);
	

    }




    // Single entry (not tokenized)
    
    else   {

    	uint ne;

    	list = entryList(fileName, entry, &ne);

    	*lsize = ne;

    }


    

    return list;
    

}
