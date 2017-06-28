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


    // Tokenize string

    uint i,ntk;

    char** tok = tokenize("DD/EE/FF",'/', &ntk);

    for(i = 0 ; i < ntk ; i++) {
	
	printf("%s\n",tok[i]);
	
    }

    printf("\n\n");

    

    uint nl;
    char** elist = entryList("input","DD", &nl);

    for(i = 0 ; i < nl ; i++) {
	
	printf("%s\n",elist[i]);
	
    }

    printf("\n\n");



    uint nsl;
    char** subel = subEntryList( elist, "EE", &nsl, nl );

    for(i = 0 ; i < nsl ; i++) {
	
    	printf("%s\n",subel[i]);
	
    }

    printf("\n\n");
    
    return 0;

}
