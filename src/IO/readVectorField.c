#include <io.h>
#include <basic.h>

unsigned int readVectorField( struct latticeMesh* mesh, double*** field, unsigned int vsize, char* fname ) {
    
    
    unsigned int status = 0;
    

    // Open file

    char name[200];

    sprintf(name, "processor%d/%d/fields.vtu", mesh->parallel.pid, mesh->time.current);

    FILE* file = fopen( name, "r" );

    rewind(file);

    


    
    *field = matrixDoubleAlloc(mesh->mesh.nPoints, vsize, 0);

    
    // Read until <PointData

    char aux[100];
    
    while( strcmp(aux, "<PointData") != 0 ) {

    	fscanf(file, "%s", aux);

    }



    uint find = 0;


    while( find == 0 ) {
    
    
    	// Read until next <DataArray
	
    	while( strcmp(aux, "<DataArray") != 0 ) {

    	    fscanf(file, "%s", aux);

    	}


    
    	// Read Name=""
    
    	fscanf(file, "%s", aux);

    	fscanf(file, "%s", aux);


	
    	// Find and extract " " delimited name

    	char auxName[20];

    	sprintf(auxName,"Name=\"%s\"",fname);


	
    	// Read if name matches
    
    	if ( strcmp(auxName, aux) == 0 ) {


    	    fscanf(file, "%s", aux);

	    fscanf(file, "%s", aux);

    	    unsigned int i,j;

    	    double value;

    	    for ( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

		for ( j = 0 ; j < vsize ; j++ ) {
		
		    fscanf(file, "%lf", &value);
		
		    field[0][i][j] = value;

		}

    	    }

    	    find = 1;

    	    status = 1;

    	}


    }
    
    
    fclose( file );

    
    return status;

}
