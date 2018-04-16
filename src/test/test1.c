#include <dictIO.h>

int main() {


    char* entry = 0;
    
    unsigned int status = lookUpStringEntry("input", "g/Y0/type", &entry, "sarasa");

    if(status)
	printf("type %s\n", entry);



    double de;
    
    status = lookUpScalarEntry("input", "g/Y0/value", 0, &de);

    if(status)
	printf("value %f\n", de);

    
    
    return 0;

}
