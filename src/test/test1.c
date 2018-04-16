#include <dictIO.h>

int main() {


    char* entry = 0;
    
    unsigned int status = lookUpStringEntry("input", "g/Y0/value", &entry, "sarasa");

    if(status)
	printf("%s\n", entry);

    
 
    
    
    return 0;

}
