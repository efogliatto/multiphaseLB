#include <dictIO.h>

int main() {


    char* entry = 0;

    unsigned int status;
    
    status = lookUpStringEntry("input", "g/Y0/type", &entry, "sarasa");

    if(status)
    	printf("type %s\n", entry);



    double de;
    
    status = lookUpScalarEntry("input", "g/Y0/value", 0, &de);

    if(status)
    	printf("value %f\n", de);



    double* ve;

    unsigned int n;
    
    status = lookUpVectorEntry("initialFields", "g/internalField/value", &ve, &n);

    if(status) {

    	unsigned int i;

    	for(i = 0 ; i < n ; i++)
    	    printf("%f ", ve[i]);
	
    	printf("\n");

    }




    printf("Found boundaryField: %d\n", isBracedEntryDefined("initialFields", "g/boundaryField") );

    printf("Found internalField: %d\n", isBracedEntryDefined("initialFields", "g/internalField") );





    status = lookUpStringEntry("initialFields", "sarasa", &entry, "");

    if(status)
    	printf("sarasa %s\n", entry);


    char** sentry;
    
    status = lookUpStringList("initialFields", "scalarFields", &sentry, &n);

    if(status) {

    	unsigned int i;

    	for(i = 0 ; i < n ; i++)
    	    printf("%s\n", sentry[i]);       

    }
    
    
    return 0;

}
