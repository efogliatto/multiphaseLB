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



    /* Multiple entries */
   
    /* printf("GG: %f\n\n\n", lookUpDouble( "input","DD/EE/FF/GG",-1) ); */
    /* printf("GG: %f\n\n\n", lookUpDouble( "input","DD/EE/FF/GG",-1) ); */
    


   
    /* double* ventry = lookUpVector("input","DD/EE/FF/II",-1,3); */

    /* uint i; */
    
    /* for(i = 0 ; i < 3 ; i++) { */
	
    /* 	printf("%f\n",ventry[i]); */
	
    /* } */

    /* printf("\n\n"); */


    

    /* ventry = lookUpVector("input","DD/EE/FF/JJ",-1,9); */
    
    /* for(i = 0 ; i < 9 ; i++) { */
	
    /* 	printf("%f\n",ventry[i]); */
	
    /* } */

    /* printf("\n\n"); */



    /* char* sentry = lookUpString("input","DD/EE/FF/HH"); */

    /* printf("HH: %s\n\n", sentry); */


    

    char* sentry = lookUpString("initialFields","U/internalField/type");

    printf("U: %s\n\n", sentry);

    sentry = lookUpString("initialFields","U/internalField/type");

    printf("U: %s\n\n", sentry);


    
    /* double* val = lookUpVector("initialFields","U/internalField/value", 0, 3); */
    
    /* printf("U: %f %f %f\n\n", val[0], val[1], val[2]); */

 
    /* double* val2 = lookUpVector("initialFields","U/internalField/value", 0, 3); */
    
    /* printf("U: %f %f %f\n\n", val2[0], val2[1], val2[2]); */



    /* uint ll; */
    /* char** sentry = lookUpEntry("initialFields","U/internalField/type", &ll); */

    /* uint i; */
    
    /* for(i = 0 ; i < ll ; i++) { */
	
    /* 	printf("%s\n",sentry[i]); */
	
    /* } */

    /* printf("\n\n"); */
    



    
    /* sentry = lookUpEntry("initialFields","U/internalField/type", &ll); */

    /* for(i = 0 ; i < ll ; i++) { */
	
    /* 	printf("%s\n",sentry[i]); */
	
    /* } */

    
    
    return 0;

}
