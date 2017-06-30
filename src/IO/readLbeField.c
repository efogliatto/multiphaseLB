#include <io.h>
#include <basic.h>
#include <readVectorField.h>

unsigned int readLbeField( struct latticeMesh* mesh, struct lbeField* field, unsigned int vsize, char* fname ) {

    
    
    // Read values from pvtu file
    
    unsigned int status = readVectorField( mesh, &field->value, mesh->mesh.Q, fname );
    
    status = readVectorField( mesh, &field->swap, mesh->mesh.Q, fname );



    
    // Read basic properties


    // Collision model
    
    char cmodel[100];

    char prop[100];

    sprintf( prop, "%s/Collision", fname);

    status = lookUpString("properties/macroProperties", prop, cmodel);


    
    if( strcmp(cmodel,"liMRT") == 0 ) {

	
	field->colId = 0;


	// Relaxation time
	
	sprintf( prop, "%s/Lambda", fname);

	double v[20];

	status = lookUpVector("properties/macroProperties", prop, v, mesh->mesh.Q);

	field->Lambda = (double*)malloc( mesh->mesh.Q * sizeof(double) );
	
	unsigned int ii;

	for( ii = 0 ; ii < mesh->mesh.Q ; ii++ ) {

	    field->Lambda[ii] = v[ii];

	}



	// Sigma constant

	sprintf( prop, "%s/sigma", fname);
	
	status = lookUpDouble("properties/macroProperties", prop, &field->sigma, 0 );
	

    }
    

    else {

	
	if( strcmp(cmodel,"liSRT") == 0 ) {

	    field->colId = 1;


	    // Relaxation time

	    sprintf( prop, "%s/tau", fname);

	    status = lookUpDouble("properties/macroProperties", prop, &field->tau, 1 );


	    // Sigma constant

	    sprintf( prop, "%s/sigma", fname);
	
	    status = lookUpDouble("properties/macroProperties", prop, &field->sigma, 0 );	    
	    

	}

	
	else {

	    
	    if( strcmp(cmodel,"liTemp") == 0 ) {

		field->colId = 2;

		
		// Relaxation time

		sprintf( prop, "%s/tau", fname);

		status = lookUpDouble("properties/macroProperties", prop, &field->tau, 1 );
		

	    }

	}

    }

    

    

    // Tau model

    sprintf( prop, "%s/tauModel", fname);

    char tm[100];
	
    status = lookUpString("properties/macroProperties", prop, tm );


    if( strcmp(tm,"constant") == 0 ) {

	field->tauModel = 0;

    }

    else {
    
	if( strcmp(tm,"constantMu") == 0 ) {

	    field->tauModel = 1;

	}

	else {
    
	    if( strcmp(tm,"constantLambda") == 0 ) {

		field->tauModel = 2;

	    }

	}	

    }
    

    
    
    return status;

}
