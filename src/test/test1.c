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
    


    unsigned int status, i, ns;

    char sentry[100][100];

    
    /* status = entryList("initialFields","scalarFields",sentry, &ns); */
    status = lookUpEntry("initialFields","scalarFields",sentry, &ns);

    if( status ) {
    
    	for(i = 0 ; i < ns ; i++) {
	
    	    printf("%s\n",sentry[i]);
	
    	}

    	printf("\n\n");

    }




    status = lookUpEntry("initialFields","U",sentry, &ns);

    if( status ) {
    
    	for(i = 0 ; i < ns ; i++) {
	
    	    printf("%s\n",sentry[i]);
	
    	}

    	printf("\n\n");

    }




    double v[3];
    
    status = lookUpVector("initialFields","U/internalField/value",v, 3);

    if( status ) {
    
    	for( i = 0 ; i < 3 ; i++ ) {
	
    	    printf("%f ",v[i]);
	
    	}

    	printf("\n");

    }


    status = lookUpVector("initialFields","U/internalField/value",v, 3);

    if( status ) {
    
    	for( i = 0 ; i < 3 ; i++ ) {
	
    	    printf("%f ",v[i]);
	
    	}

    	printf("\n\n\n");

    }    
    


    char ftype[100];
    
    status = lookUpString("initialFields","U/internalField/type",ftype );

    if( status ) {  printf("%s\n",ftype);   }

    status = lookUpString("initialFields","U/internalField/type",ftype );

    if( status ) {  printf("%s\n\n\n",ftype);   }    




    
    
    
    return 0;

}
