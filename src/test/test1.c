#include <io.h>

int main() {

    // Read basic Entries
    double a = lookUpDoubleEntry("input","AA",-1);
    double b = lookUpDoubleEntry("input","BB",-1);
    char c[100];
    lookUpStringEntry("input","CC", c);

    printf("\n");
    printf("a = %f\n",a);
    printf("b = %f\n",b);
    printf("c = %s\n",c);    
    printf("\n");



    // Multiple entries
    
    uint i,lsize;

    char** entry = lookUpEntry("input","DD/EE/FF/JJ",&lsize);
    
    for(i = 0 ; i < lsize ; i++) {
	
    	printf("%s\n",entry[i]);
	
    }

    printf("\n\n");
    


    entry = lookUpEntry("input","AAA/BBB",&lsize);
    
    for(i = 0 ; i < lsize ; i++) {
	
    	printf("%s\n",entry[i]);
	
    }

    printf("\n\n");
    
    
    return 0;

}
