#include <io.h>
#include <basic.h>
#include <readVectorField.h>

unsigned int readLbeField( struct latticeMesh* mesh, struct lbeField* field, char* fname ) {

    
    
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

    field->tauModel = 0;
	
    status = lookUpString("properties/macroProperties", prop, tm );

    if( status ) {

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
    
    }
    




    // Read boundary conditions

    field->boundary = (struct bdField*)malloc( mesh->mesh.bd.nbd * sizeof(struct bdField) );
    
    unsigned int i;

    for( i = 0 ; i < mesh->mesh.bd.nbd ; i++ ) {


	char bdType[100];

	uint jj = 0;

	for( jj = 0 ; jj < 100 ; jj++ ) {

	    bdType[jj] = '\0';

	    prop[jj] = '\0';

	    cmodel[jj] = '\0';

	}


	sprintf(prop,"%s/%s/type",fname,mesh->mesh.bd.bdNames[i]);

	sprintf(cmodel,"%s/%s/value",fname,mesh->mesh.bd.bdNames[i]);

	
	status = lookUpString("start/boundaries", prop, bdType);

	if( strcmp(bdType, "periodic") == 0 ) {

	    field->boundary[i].bdType = 0;

	}

	else {

	    if( strcmp(bdType, "bounceBack") == 0 ) {

		field->boundary[i].bdType = 1;

	    }

	    else {

		if( strcmp(bdType, "fixedU") == 0 ) {

		    field->boundary[i].bdType = 2;

		    double v[3];
		    
		    status = lookUpVector("start/boundaries", cmodel, v, 3);

		    for( jj = 0 ; jj < 3 ; jj++ ) {

			field->boundary[i].vectorVal[jj] = v[jj];

		    }

		}

		else {

		    if( strcmp(bdType, "fixedT") == 0 ) {

			field->boundary[i].bdType = 3;

			status = lookUpDouble("start/boundaries", cmodel, &field->boundary[i].scalarVal, 0);

		    }

		    else {



		    }

		}

	    }

	}
	

    }

    
    return status;

}
