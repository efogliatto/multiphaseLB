#include <dictIO.h>

int main() {

    // Open dictionary
    
    struct dictionary dict = openDict("input");


    char* entry = 0;

    unsigned int status;
    
    status = bracedEntry( "g", dict.content, &entry );

    if(status) {
	
	status = bracedEntry( "Y0", entry, &entry );

	if(status) {
	
	    status = singleEntry( "value", entry, &entry );

	    printf("%s\n",entry);

	}


    }
  



    
    
    return 0;

}
