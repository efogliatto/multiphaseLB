#include <vectorDivergence.h>
#include <basic.h>


scalar vectorDivergence( scalar** field, latticeMesh* mesh, uint id ) {


    // Neighbours
    int a;
    int b;

    scalar div = 0;
  

    // D2Q9 model

    switch( mesh->lattice.model ) {

	
    case D2Q9:
    

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

	

	break;

    



    case D3Q15:


    	// X - derivative

    	a = mesh->mesh.nb[id][2];
	
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
	
    	b = mesh->mesh.nb[id][3];

	
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




    	// Z - derivative

    	a = mesh->mesh.nb[id][6];
	
    	b = mesh->mesh.nb[id][5];

	
    	if(  (a != -1)  &&  (b != -1)  ) {
    
    	    div += 0.5 * (field[a][2] - field[b][2]);

    	}

    	else {

    	    if(  (a == -1)  &&  (b != -1)  ) {
    
    		div += (field[id][2] - field[b][2]);

    	    }

    	    else {

    		if(  (a != -1)  &&  (b == -1)  ) {
    
    		    div += (field[a][2] - field[id][2]);

    		}

    	    }

    	}   



	

	break;



    default:

	errorMsg("Finite difference scheme not implemented");

	break;	



	
    }    


    return div;

}
