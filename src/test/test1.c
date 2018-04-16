#include <dictIO.h>

int main() {


    char* entry = 0;
    
    unsigned int status = lookUpEntry("input", "g/Y0/value", &entry);

    if(status)
	printf("%s\n", entry);
    
 
    
    
    return 0;

}
