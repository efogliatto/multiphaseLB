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

	printf("%s\n", entry2);

    }

    
    
    return 0;

}
