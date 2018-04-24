#include <scalarGradient.h>
#include <basic.h>


void scalarGradient( double* grad, double* field, latticeMesh* mesh, unsigned int id ) {


    // Neighbours
    int a;
    int b;
  

    // D2Q9 model

    switch(mesh->lattice.model) {

    case D2Q9:
    

    	// X - derivative

    	a = mesh->mesh.nb[id][3];
    	b = mesh->mesh.nb[id][1];
    
    	if(  (a != -1)  &&  (b != -1)  ) {
    
    	    grad[0] = 0.5 * (field[a] - field[b]);

    	}

    	else {

    	    if(  (a == -1)  &&  (b != -1)  ) {
    
    		grad[0] = (field[id] - field[b]);

    	    }

    	    else {

    		if(  (a != -1)  &&  (b == -1)  ) {
    
    		    grad[0] = (field[a] - field[id]);

    		}

    		else {

    		    grad[0] = 0;

    		}

    	    }

    	}




    	// Y - derivative

    	a = mesh->mesh.nb[id][4];
    	b = mesh->mesh.nb[id][2];
    
    	if(  (a != -1)  &&  (b != -1)  ) {
    
    	    grad[1] = 0.5 * (field[a] - field[b]);

    	}

    	else {

    	    if(  (a == -1)  &&  (b != -1)  ) {
    
    		grad[1] = (field[id] - field[b]);

    	    }

    	    else {

    		if(  (a != -1)  &&  (b == -1)  ) {
    
    		    grad[1] = (field[a] - field[id]);

    		}

    		else {

    		    grad[0] = 0;

    		}

    	    }

    	}
    

    	grad[2] = 0.0;

	break;


	
    case D3Q15:

	errorMsg("Finite difference scheme not implemented for D3Q15");

	break;



    default:

	errorMsg("Finite difference scheme not implemented");

	break;	


	

    }
    


}
