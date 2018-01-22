#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>

void invScalarGradient( double* grad, double* field, struct latticeMesh* mesh, unsigned int id ) {


    // Neighbours
    int a;
    int b;
  

    // D2Q9 model

    if(   ( mesh->lattice.d == 2 )  &&  ( mesh->lattice.Q == 9 )   )  {
    

    	// X - derivative

    	a = mesh->mesh.nb[id][3];
    	b = mesh->mesh.nb[id][1];
    
    	if(  (a != -1)  &&  (b != -1)  ) {
    
    	    grad[0] = 0.5 * (1.0/field[a] - 1.0/field[b]);

    	}

    	else {

    	    if(  (a == -1)  &&  (b != -1)  ) {
    
    		grad[0] = (1.0/field[id] - 1.0/field[b]);

    	    }

    	    else {

    		if(  (a != -1)  &&  (b == -1)  ) {
    
    		    grad[0] = (1.0/field[a] - 1.0/field[id]);

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
    
    	    grad[1] = 0.5 * (1.0/field[a] - 1.0/field[b]);

    	}

    	else {

    	    if(  (a == -1)  &&  (b != -1)  ) {
    
    		grad[1] = (1.0/field[id] - 1.0/field[b]);

    	    }

    	    else {

    		if(  (a != -1)  &&  (b == -1)  ) {
    
    		    grad[1] = (1.0/field[a] - 1.0/field[id]);

    		}

    		else {

    		    grad[0] = 0;

    		}

    	    }

    	}
    

    	grad[2] = 0.0;


    }



    
    else {

    	printf("\n  [ERROR]  Gradient function not defined\n\n");

    	exit(0);

    }

}
