/*

  Multiphase solver with heat transfer

 */


#include <io.h>
#include <latticeModel.h>
#include <basic.h>
#include <mpi.h>
#include <generalLbe.h>
#include <pseudoPot.h>




int main( int argc, char **argv ) {



    // Check for arguments
    uint ht = 1, frozen = 1;
    {
    	uint arg;
    	for( arg = 0 ; arg < argc ; arg++) {

    	    if ( strcmp("--nht", argv[arg]) == 0 ) {
    		ht = 0;
    	    }

    	    else {

    		if ( strcmp("--frozen", argv[arg]) == 0 ) {
    		    frozen = 0;
    		}
		
    	    }
	    
    	}
    }


    

    int pid, world;
    
    // Initialize mpi
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&pid);
    MPI_Comm_size(MPI_COMM_WORLD,&world);
    
    if(pid == 0) {
    	printf("                    \n");
    	printf("     o-----o-----o  \n");
    	printf("     | -   |   - |  \n");
    	printf("     |   - | -   |  \n");
    	printf("     o<----o---->o       Two Phases - Lattice-Boltzmann solver with heat transfer. Pseudopotential model\n");
    	printf("     |   - | -   |  \n");
    	printf("     | -   |   - |  \n");
    	printf("     o-----o-----o  \n");
    }



    
    // Simulation properties
    
    latticeMesh mesh = readLatticeMesh( pid );

    mesh.lattice = setLatticeInfo();

    mesh.EOS = readEOSInfo();

    vtkInfo vtk = readVTKInfo();
    

    
    

    // Macroscopic fields
    
    macroFields mfields;
    

    
    // Density

    createScalarField( &mesh, &mfields.rho, "rho", MUST_READ);

    mesh.EOS.rho_0 = averageScalarField(&mesh, mfields.rho);


    
    
    /* // Velocity */

    /* createVectorField( &mesh, &mfields.U, 3, "U", MUST_READ); */
    

    
    // Temperature

    createScalarField( &mesh, &mfields.T, "T", MUST_READ);



    // Pressure

    createScalarField( &mesh, &mfields.p, "p", MUST_READ);
    
    


    /* // LBE fields */

    /* // Navier-Stokes field */

    /* lbeField f; */
    
    /* createLbeField( &mesh, &f, "f", MUST_READ); */

    /* if(frozen == 0) { f.update = 0; } */


    
    /* // Energy field */

    /* lbeField g; */
    
    /* createLbeField( &mesh, &g, "g", MUST_READ); */

    /* if(ht == 0) { g.update = 0; } */
    
    

    /* /\* // Initial equilibrium distribution *\/ */
   
    /* /\* equilibrium(&mesh, &mfields, &f); *\/ */
    
    /* /\* equilibrium(&mesh, &mfields, &g); *\/ */


    if(pid == 0) { printf( "\n"); }
    


    
    // Advance in time. Collide, stream, update and write
    
    while( updateTime(&mesh.time) ) {

	
	
    	// Write fields
	
    	if( writeFlag(&mesh.time) ) {

	    
    	    if(pid == 0) {
		
    		printf( "Time = %d\n", mesh.time.current );
		
    		printf("Elapsed time = %.2f seconds\n\n", elapsed(&mesh.time) );
		
    	    }
	   

	    
    	    // Write

    	    if(mesh.time.data == pvtu) {
	    
    		writeMeshToVTK( &mesh, &vtk );

    	    }

    	    if(mesh.time.data == ensight) {

    		updateCaseFile(&mesh);

    	    }
	    

    	    writeScalarField( "rho", mfields.rho, &mesh );

    	    writeScalarField( "T", mfields.T, &mesh );

    	    writeScalarField( "p", mfields.p, &mesh );

    	    /* writeVectorField( "U", mfields.U, &mesh, 3 ); */

    	    /* writeVectorField( "f", f.value, &mesh, mesh.lattice.Q ); */

    	    /* writeVectorField( "g", g.value, &mesh, mesh.lattice.Q ); */


    	    if(mesh.time.data == pvtu) {
	    
    		writePvtuExtra( &mesh, &vtk );

    		writeMainPvd();

    	    }


	    
	    
    	}
	

    }


    
    // Print info
    if(pid == 0) {
	
    	printf("\n  Finished in %.2f seconds \n\n", elapsed(&mesh.time) );
	
    }


    
    MPI_Finalize();

    
    return 0;
    
}
