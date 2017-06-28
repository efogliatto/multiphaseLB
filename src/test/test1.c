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
    



    
    return 0;

}
