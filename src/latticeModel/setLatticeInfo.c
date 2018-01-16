#include <setLatticeInfo.h>
#include <io.h>
#include <cs2.h>
#include <latticeVelocities.h>
#include <latticeReverseDir.h>
#include <latticeWeights.h>
#include <ppWeights.h>
#include <MRTMatrix.h>
#include <MRTInvMatrix.h>


unsigned int latticeQ( char* modelName );

unsigned int latticeD( char* modelName );


struct latticeInfo setLatticeInfo( ) {


    // Read model name    
    
    char* modelName = (char*)malloc( 10*sizeof(char) );

    unsigned int i;

    for( i = 0 ; i < 10 ; i++ ) {

	modelName[i] = '\0';

    }

    char lbm[20];

    lookUpStringEntry("properties/latticeProperties","LBModel", lbm);

    strcpy(modelName, lbm);
    



    // Assign properties
    
    struct latticeInfo info;
    
    info.cs2 = cs2( modelName );

    info.Q = latticeQ( modelName );

    info.d = latticeD( modelName );

    info.vel = latticeVelocities( modelName );

    info.reverse = latticeReverseDir( modelName );

    info.omega = latticeWeights( modelName );

    info.weights = ppWeights( modelName );

    info.M = MRTMatrix( modelName );

    info.invM = MRTInvMatrix( modelName );
    


    

    free(modelName);
    
    return info;

}
