#include <dictIO.h>

int main() {

    // Open dictionary
    
    struct dictionary dict = openDict("input");


    char* entry = 0;

    unsigned int status;
    
    status = bracedEntry( "g", dict.content, &entry );

    if(status) {
	
	char* entry2 = 0;
	
	status = bracedEntry( "Y0", entry, &entry2 );

	/* printf("%s\n",entry2); */

	if(status) {
	
	    char* entry3 = 0;
	
	    status = singleEntry( "value", entry2, &entry3 );

	    /* printf("%s\n",entry3); */

	}


    }

    
    
    return 0;

}
