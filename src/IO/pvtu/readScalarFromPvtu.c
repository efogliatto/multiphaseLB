#include <io.h>
#include <stdlib.h>
#include <readScalarFromPvtu.h>

uint readScalarFromPvtu( latticeMesh* mesh, scalar** field, char* fname ) {

    
    unsigned int status = 0;
    

    // Open file

    char name[200];

    sprintf(name, "processor%d/%d/fields.vtu", mesh->parallel.pid, mesh->time.current);

    FILE* file = fopen( name, "r" );

    rewind(file);

    


    
    *field = (scalar*)malloc( mesh->mesh.nPoints * sizeof(scalar) );

    
    // Read until <PointData

    char aux[100];
    
    while( strcmp(aux, "<PointData") != 0 ) {

    	status = fscanf(file, "%s", aux);

    }



    uint find = 0;


    while( find == 0 ) {
    
    
    	// Read until next <DataArray
	
    	while( strcmp(aux, "<DataArray") != 0 ) {

    	    status = fscanf(file, "%s", aux);

    	}


    
    	// Read Name=""
    
    	status = fscanf(file, "%s", aux);

    	status = fscanf(file, "%s", aux);


	
    	// Find and extract " " delimited name

    	char auxName[20];

    	sprintf(auxName,"Name=\"%s\"",fname);


	
    	// Read if name matches
    
    	if ( strcmp(auxName, aux) == 0 ) {


    	    status = fscanf(file, "%s", aux);

    	    unsigned int i;

	    scalar value;

    	    for ( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

		#ifdef DP
		
    	    	status = fscanf(file, "%lf", &value);

		#elif SP

    	    	status = fscanf(file, "%f", &value);

		#endif
		
		field[0][i] = value;

    	    }

    	    find = 1;

    	    status = 1;

    	}


    }
    
    
    fclose( file );

    
    return status;

}
