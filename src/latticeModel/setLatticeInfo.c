#include <setLatticeInfo.h>
#include <dictIO.h>
#include <cs2.h>
#include <latticeQ.h>
#include <latticeD.h>
#include <latticeVelocities.h>
#include <latticeReverseDir.h>
#include <latticeWeights.h>
#include <ppWeights.h>
#include <MRTMatrix.h>
#include <MRTInvMatrix.h>
#include <errorMsg.h>



latticeInfo setLatticeInfo( ) {


    
    uint status;

    char* modelName;

    latticeInfo info;

    info.model = D2Q9;


    
    // Read model name. Use D2Q9 as default
    
    status = lookUpStringEntry( "properties/latticeProperties", "LBModel", &modelName, "D2Q9" );

    if(status) {}

    if( strcmp(modelName, "D2Q9") == 0 ) {

	info.model = D2Q9;

    }

    else {

	if( strcmp(modelName, "D3Q15") == 0 ) {

	    info.model = D3Q15;

	}

	else {

	    char msg[100];

	    sprintf(msg, "Unrecognized model %s", modelName);
	    
	    errorMsg( msg );

	}

    }

    
    
    

    // Assign properties        
    
    info.cs2 = cs2( info.model );

    info.Q = latticeQ( info.model );

    info.d = latticeD( info.model );

    info.vel = latticeVelocities( info.model );

    info.reverse = latticeReverseDir( info.model );

    info.omega = latticeWeights( info.model );

    info.weights = ppWeights( info.model );

    info.M = MRTMatrix( info.model );

    info.invM = MRTInvMatrix( info.model );
    
  
    
    return info;

}
