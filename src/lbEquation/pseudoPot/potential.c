#include <potential.h>
#include <p_eos.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

scalar potential( latticeMesh* mesh, scalar rho, scalar T ) {
    
    return sqrt(
    	2 * ( p_eos(&mesh->EOS,rho,T) - rho * mesh->lattice.cs2 ) / (mesh->EOS.G)
    	);
    
}
