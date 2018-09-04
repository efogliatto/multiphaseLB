#include <dictIO.h>
#include <basic.h>
#include <readVectorField.h>
#include <readLbeField.h>
#include <readLiMRTConstants.h>
#include <readLiTempMRTConstants.h>
#include <readMyMRTConstants.h>
#include <readXuMRTConstants.h>
#include <readFixedGradTParam.h>



uint readLbeField( latticeMesh* mesh, lbeField* field, char* fname ) {

    
    
    // Read values from pvtu file
    
    uint status = readVectorField( mesh, &field->value, mesh->mesh.Q, fname );
    
    status = readVectorField( mesh, &field->swap, mesh->mesh.Q, fname );



    
    // Read lbmodel type

    char* entry;

    char* str;

    status = vstring(&entry, "%s/Collision", fname);

    status = lookUpStringEntry("properties/macroProperties", entry, &str, "");

    if(!status)
    	errorMsg("Collision model not found");

    
    if( strcmp(str,"liMRT") == 0 ) {

    	field->model = liMRT;

    }

    else {

    	if( strcmp(str,"myMRT") == 0 ) {

    	    field->model = myMRT;

    	}

	else {

	    if( strcmp(str,"xuMRT") == 0 ) {

		field->model = xuMRT;

	    }

	    else {

		if( strcmp(str,"liTempMRT") == 0 ) {

		    field->model = liTempMRT;

		}

	    }
	    

	}

    }





    // Read basic properties

    switch( field->model ) {
	

    case liMRT:

    	field->lbparam.liMRT = readLiMRTConstants( fname );

    	break;
	

    case myMRT:

    	field->lbparam.myMRT = readMyMRTConstants( fname );

	
    	// Allocate scalar source
	
    	field->scalarSource = (scalar*)malloc( mesh->mesh.nPoints * sizeof(scalar) );

    	break;
	

    case xuMRT:

    	field->lbparam.xuMRT = readXuMRTConstants( fname );

    	break;

	

    case liTempMRT:

    	field->lbparam.liTempMRT = readLiTempMRTConstants( fname );

	
    	// Allocate scalar source
	
    	field->scalarSource = (scalar*)malloc( mesh->mesh.nPoints * sizeof(scalar) );

    	break;
	

    }


    
    // Enable field update

    field->update = 1;


    


    // Read boundary conditions

    field->boundary = (bdField*)malloc( mesh->mesh.bd.nbd * sizeof(bdField) );
    
    uint i;

    for( i = 0 ; i < mesh->mesh.bd.nbd ; i++ ) {

    	status = vstring(&entry, "%s/%s/type", fname, mesh->mesh.bd.bdNames[i]);

    	status = lookUpStringEntry("start/boundaries", entry, &str, "");

    	if(!status) {

    	    status = vstring(&str, "Unable to find entry %s", entry);
	    
    	    errorMsg(str);

    	}

    	else {
	    

    	    if( strcmp(str, "bounceBack") == 0 ) {

    		field->boundary[i].type = bback;

    	    }

	    
    	    if( strcmp(str, "periodic") == 0 ) {

    		field->boundary[i].type = periodic;

    	    }

	    
    	    if( strcmp(str, "fixedT") == 0 ) {

    		field->boundary[i].type = ft;

    		field->boundary[i].param.ft = readFixedTParam(fname, mesh->mesh.bd.bdNames[i]);

    	    }

	    
    	    if( strcmp(str, "fixedRandomT") == 0 ) {

    		field->boundary[i].type = frdt;

    		field->boundary[i].param.frdt = readFixedRandomTParam(fname, mesh->mesh.bd.bdNames[i]);

    	    }
	    
	    
    	    if( strcmp(str, "fixedU") == 0 ) {

    		field->boundary[i].type = fu;

    		field->boundary[i].param.fu = readFixedUParam(fname, mesh->mesh.bd.bdNames[i]);

    	    }

	    
    	    if( strcmp(str, "outflow") == 0 ) {

    		field->boundary[i].type = of;

    	    }



    	    if( strcmp(str, "fixedGradT") == 0 ) {

    		field->boundary[i].type = fgt;

    		field->boundary[i].param.fgt = readFixedGradTParam(fname, mesh->mesh.bd.bdNames[i]);		       		

    	    }	    
	    

    	}
	

    }



    // Release memory
    
    free(entry);

    free(str);







    // Allocate mpi buffers

    field->rbuf = (scalar**)malloc( mesh->parallel.worldSize * sizeof(scalar*) );
    
    for( i = 0 ; i < mesh->parallel.worldSize ; i++ )
    	field->rbuf[i] = (scalar*)malloc( mesh->parallel.nrg[i] * mesh->mesh.Q * sizeof(scalar) );



    field->sbuf = (scalar**)malloc( mesh->parallel.worldSize * sizeof(scalar*) );
    
    for( i = 0 ; i < mesh->parallel.worldSize ; i++ )
    	field->sbuf[i] = (scalar*)malloc( mesh->parallel.nsg[i] * mesh->mesh.Q * sizeof(scalar) );

    



    
    
    return status;

}
