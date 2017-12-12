#include <stdlib.h>

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

#include <liMRTModel.h>
#include <liSRTModel.h>
#include <liTempModel.h>
#include <newTempModel.h>
#include <myMRTModel.h>


void equilibrium( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    
    // Apply equilibrium model according to field.colId

    unsigned int id;
    
    switch(field->colId) {

	
    // Li model. MRT version
	
    case 0:
	
	for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

	    liMRTEquilibrium( &mesh->lattice, mfields->rho[id], mfields->U[id], field->value[id] );

	}
	
	break;

	
    // Li model. SRT version
	
    case 1:
	
	for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

	    liSRTEquilibrium( &mesh->lattice, mfields->rho[id], mfields->U[id], field->value[id] );

	}
	
	break;
	
	

    // Li model. Temperature
	
    case 2:
	
	for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

	    liTempEquilibrium( &mesh->lattice, mfields->rho[id], mfields->U[id], field->value[id] );

	    unsigned int k;

	    for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

		field->value[id][k] = field->value[id][k] * mesh->EOS._Cv * mfields->T[id];
	    
	    }
	    
	}

	
	break;



    // new model. Temperature
	
    case 3:
	
	for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

	    newTempEquilibrium( &mesh->lattice, mfields->rho[id], mfields->U[id], field->value[id] );

	    unsigned int k;

	    for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

		field->value[id][k] = field->value[id][k] * mesh->EOS._Cv * mfields->T[id];
	    
	    }
	    
	}

	
	break;
	



    // new MRT model. Temperature
	
    case 4:
	
	for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

	    myMRTEquilibrium( &mesh->lattice, mfields->rho[id], mfields->U[id], field->value[id] );

	    unsigned int k;

	    for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

		field->value[id][k] = field->value[id][k] * mesh->EOS._Cv * mfields->T[id];
	    
	    }
	    
	}

	
	break;
	

    default:

	printf("\n   [ERROR]  Unrecognized collision model\n\n");

	exit(1);
	
	break;
	
    }
    
}
