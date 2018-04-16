#include <dictIO.h>

int main() {

    
    // Open dictionary
    
    struct dictionary dict = openDict("input");


    /* char* entry = 0; */

    char** tk;

    unsigned int n, i;

    unsigned int status;

    status = tokenize("value", &tk, &n);

    for( i = 0 ; i < n ; i++ ) {

	printf("%s\n", tk[i]);

    }

    
    
    /* status = bracedEntry( "g", dict.content, &entry ); */

    /* if(status) { */
	
    /* 	status = bracedEntry( "Y0", entry, &entry ); */

    /* 	if(status) { */
	
    /* 	    status = singleEntry( "value", entry, &entry ); */

    /* 	    printf("%s\n",entry); */

    /* 	} */


    /* } */
    
  



    
    
    return 0;

}
