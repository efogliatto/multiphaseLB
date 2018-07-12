#include <xuMRTPressure.h>
#include <potential.h>
#include <basic.h>


scalar xuMRTPressure( latticeMesh* mesh, lbeField* field, scalar* rho, scalar* T, scalar sigma, uint id ) {



    scalar psi = potential(mesh, rho[id], T[id]);

    scalar p = rho[id] * mesh->lattice.cs2    +    0.5 * mesh->EOS.G * psi * psi;


    
    // Laplacian of potential

    scalar lap = 0;

    int a;

    int b;

    int c;
    

    switch(mesh->lattice.model) {


    case D3Q15:


    	// X - derivative

    	a = mesh->mesh.nb[id][2];

    	b = mesh->mesh.nb[id][1];

	
    	if(  (a != -1)  &&  (b != -1)  ) {
    
    	    lap = potential(mesh, rho[a], T[a])  +  potential(mesh, rho[b], T[b])  -  2 * potential(mesh, rho[id], T[id]);

    	}

    	else {

    	    if(  (a == -1)  &&  (b != -1)  ) {

		c = mesh->mesh.nb[b][1];
		
		lap = potential(mesh, rho[c], T[c])  -   2 * potential(mesh, rho[b], T[b])  +  potential(mesh, rho[id], T[id]);

    	    }

    	    else {

    		if(  (a != -1)  &&  (b == -1)  ) {
    
		    c = mesh->mesh.nb[a][2];
		
		    lap = potential(mesh, rho[c], T[c])  -   2 * potential(mesh, rho[a], T[a])  +  potential(mesh, rho[id], T[id]);    

    		}

    		else {

    		    lap = 0;

    		}

    	    }

    	}




    	// Y - derivative

    	a = mesh->mesh.nb[id][4];

    	b = mesh->mesh.nb[id][3];

	
    	if(  (a != -1)  &&  (b != -1)  ) {
    
	    lap = lap + potential(mesh, rho[a], T[a])  +  potential(mesh, rho[b], T[b])  -  2 * potential(mesh, rho[id], T[id]);

    	}

    	else {

    	    if(  (a == -1)  &&  (b != -1)  ) {
    
		c = mesh->mesh.nb[b][3];
		
		lap = lap + potential(mesh, rho[c], T[c])  -   2 * potential(mesh, rho[b], T[b])  +  potential(mesh, rho[id], T[id]);

    	    }

    	    else {

    		if(  (a != -1)  &&  (b == -1)  ) {
    
		    c = mesh->mesh.nb[a][4];
		
		    lap = lap + potential(mesh, rho[c], T[c])  -   2 * potential(mesh, rho[a], T[a])  +  potential(mesh, rho[id], T[id]);    

    		}

    		else {


    		}

    	    }

    	}






    	// Z - derivative

    	a = mesh->mesh.nb[id][6];

    	b = mesh->mesh.nb[id][5];

	
    	if(  (a != -1)  &&  (b != -1)  ) {
    
	    lap = lap + potential(mesh, rho[a], T[a])  +  potential(mesh, rho[b], T[b])  -  2 * potential(mesh, rho[id], T[id]);

    	}

    	else {

    	    if(  (a == -1)  &&  (b != -1)  ) {
    
		c = mesh->mesh.nb[b][5];
		
		lap = lap + potential(mesh, rho[c], T[c])  -   2 * potential(mesh, rho[b], T[b])  +  potential(mesh, rho[id], T[id]);

    	    }

    	    else {

    		if(  (a != -1)  &&  (b == -1)  ) {
    
		    c = mesh->mesh.nb[a][6];
		
		    lap = lap + potential(mesh, rho[c], T[c])  -   2 * potential(mesh, rho[a], T[a])  +  potential(mesh, rho[id], T[id]);    

    		}

    		else {


    		}

    	    }

    	}


	
	
	
	break;



    default:

	break;


    }


    scalar kappa = 0;

    if( field->lbparam.xuMRT.surfaceTension == xuSurfTen ) {

	kappa = field->lbparam.xuMRT.kappa_st;

    }

    
    p = p   +   mesh->EOS.G * psi * lap * (1 + 2*kappa)/ 12;






    // Gradient of potential

    scalar grad[3] = {0,0,0};
    
    switch(mesh->lattice.model) {

    case D3Q15:
    

    	// X - derivative

    	a = mesh->mesh.nb[id][2];
    	b = mesh->mesh.nb[id][1];
    
    	if(  (a != -1)  &&  (b != -1)  ) {
    
    	    grad[0] = 0.5 * (potential(mesh, rho[a], T[a]) - potential(mesh, rho[b], T[b]));

    	}

    	else {

    	    if(  (a == -1)  &&  (b != -1)  ) {
    
    		grad[0] = (potential(mesh, rho[id], T[id]) - potential(mesh, rho[b], T[b]));

    	    }

    	    else {

    		if(  (a != -1)  &&  (b == -1)  ) {
    
    		    grad[0] = (potential(mesh, rho[a], T[a]) - potential(mesh, rho[id], T[id]));

    		}

    		else {

    		    grad[0] = 0;

    		}

    	    }

    	}




    	// Y - derivative

    	a = mesh->mesh.nb[id][4];
    	b = mesh->mesh.nb[id][3];
    
    	if(  (a != -1)  &&  (b != -1)  ) {
    
    	    grad[1] = 0.5 * (potential(mesh, rho[a], T[a]) - potential(mesh, rho[b], T[b]));

    	}

    	else {

    	    if(  (a == -1)  &&  (b != -1)  ) {
    
    		grad[1] = (potential(mesh, rho[id], T[id]) - potential(mesh, rho[b], T[b]));

    	    }

    	    else {

    		if(  (a != -1)  &&  (b == -1)  ) {
    
    		    grad[1] = (potential(mesh, rho[a], T[a]) - potential(mesh, rho[id], T[id]));

    		}

    		else {

    		    grad[1] = 0;

    		}

    	    }

    	}







    	// Z - derivative

    	a = mesh->mesh.nb[id][6];
    	b = mesh->mesh.nb[id][5];
    
    	if(  (a != -1)  &&  (b != -1)  ) {
    
    	    grad[2] = 0.5 * (potential(mesh, rho[a], T[a]) - potential(mesh, rho[b], T[b]));

    	}

    	else {

    	    if(  (a == -1)  &&  (b != -1)  ) {
    
    		grad[2] = (potential(mesh, rho[id], T[id]) - potential(mesh, rho[b], T[b]));

    	    }

    	    else {

    		if(  (a != -1)  &&  (b == -1)  ) {
    
    		    grad[2] = (potential(mesh, rho[a], T[a]) - potential(mesh, rho[id], T[id]));

    		}

    		else {

    		    grad[2] = 0;

    		}

    	    }

    	}


	break;


	


    default:	

	break;	
	

    }





    p = p + 2.0 * mesh->EOS.G * mesh->EOS.G * sigma * vectorMag2(grad);
    
    

    return p;
	
}
