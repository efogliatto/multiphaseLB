#include <liMRTPressure.h>
#include <potential.h>

double liMRTPressure( latticeMesh* mesh, double* rho, double* T, unsigned int id ) {



    double psi = potential(mesh, rho[id], T[id]);

    double p = rho[id] * mesh->lattice.cs2    +    0.5 * mesh->EOS.G * psi * psi;


    
    // Laplacian of potential

    double lap = 0;

    int a;

    int b;

    int c;
    

    switch(mesh->lattice.model) {


    case D2Q9:


    	// X - derivative

    	a = mesh->mesh.nb[id][3];

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
    
		    c = mesh->mesh.nb[a][3];
		
		    lap = potential(mesh, rho[c], T[c])  -   2 * potential(mesh, rho[a], T[a])  +  potential(mesh, rho[id], T[id]);    

    		}

    		else {

    		    lap = 0;

    		}

    	    }

    	}




    	/* // Y - derivative */

    	/* a = mesh->mesh.nb[id][4]; */
    	/* b = mesh->mesh.nb[id][2]; */
    
    	/* if(  (a != -1)  &&  (b != -1)  ) { */
    
    	/*     grad[1] = 0.5 * (field[a] - field[b]); */

    	/* } */

    	/* else { */

    	/*     if(  (a == -1)  &&  (b != -1)  ) { */
    
    	/* 	grad[1] = (field[id] - field[b]); */

    	/*     } */

    	/*     else { */

    	/* 	if(  (a != -1)  &&  (b == -1)  ) { */
    
    	/* 	    grad[1] = (field[a] - field[id]); */

    	/* 	} */

    	/* 	else { */

    	/* 	    grad[0] = 0; */

    	/* 	} */

    	/*     } */

    	/* } */
    

    	/* grad[2] = 0.0; */
	
	
	break;



    default:

	break;


    }


    p = p   +   mesh->EOS.G * psi * lap / 12;

    
    /* // Move over velocities */
	
    /* for(k = 0 ; k < mesh->lattice.Q ; k++) { */

    /* 	rho += f[k]; */

    /* } */

    return p;
	
}
