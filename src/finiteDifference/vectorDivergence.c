#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>

double vectorDivergence( double** field, struct latticeMesh* mesh, unsigned int id ) {


    // Neighbours
    int a;
    int b;

    double div = 0;
  

    // D2Q9 model

    if(   ( mesh->lattice.d == 2 )  &&  ( mesh->lattice.Q == 9 )   )  {
    

    	// X - derivative

    	a = mesh->mesh.nb[id][3];
	
    	b = mesh->mesh.nb[id][1];

	
    	if(  (a != -1)  &&  (b != -1)  ) {
    
    	    div += 0.5 * (field[a][0] - field[b][0]);

    	}

    	else {

    	    if(  (a == -1)  &&  (b != -1)  ) {
    
    		div += (field[id][0] - field[b][0]);

    	    }

    	    else {

    		if(  (a != -1)  &&  (b == -1)  ) {
    
    		    div += (field[a][0] - field[id][0]);

    		}

    	    }

    	}




    	// Y - derivative

    	a = mesh->mesh.nb[id][4];
	
    	b = mesh->mesh.nb[id][2];

	
    	if(  (a != -1)  &&  (b != -1)  ) {
    
    	    div += 0.5 * (field[a][1] - field[b][1]);

    	}

    	else {

    	    if(  (a == -1)  &&  (b != -1)  ) {
    
    		div += (field[id][1] - field[b][1]);

    	    }

    	    else {

    		if(  (a != -1)  &&  (b == -1)  ) {
    
    		    div += (field[a][1] - field[id][1]);

    		}

    	    }

    	}   


    }



    
    else {

    	printf("\n  [ERROR]  Divergence function not defined\n\n");

    	exit(0);

    }



    return div;

}
