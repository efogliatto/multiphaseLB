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

  

    int pid, world;
    
    // Initialize mpi
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&pid);
    MPI_Comm_size(MPI_COMM_WORLD,&world);
    
    /* if(pid == 0) { */
    /* 	printf("                    \n"); */
    /* 	printf("     o-----o-----o  \n"); */
    /* 	printf("     | -   |   - |  \n"); */
    /* 	printf("     |   - | -   |  \n"); */
    /* 	printf("     o<----o---->o       Two Phases - Lattice-Boltzmann solver with heat transfer. Pseudopotential model\n"); */
    /* 	printf("     |   - | -   |  \n"); */
    /* 	printf("     | -   |   - |  \n"); */
    /* 	printf("     o-----o-----o  \n"); */
    /* } */



    
    // Simulation properties
    
    latticeMesh mesh = readLatticeMesh( pid );

    mesh.lattice = setLatticeInfo();

    mesh.EOS = readEOSInfo();

    vtkInfo vtk = readVTKInfo();
    

    
    

    // Macroscopic fields
    
    macroFields mfields;
    

    
    // Density

    createScalarField( &mesh, &mfields.rho, "rho", MUST_READ);

    
    
    // Velocity

    createVectorField( &mesh, &mfields.U, 3, "U", MUST_READ);
    

    
    // Temperature

    createScalarField( &mesh, &mfields.T, "T", MUST_READ);



    // LBE fields

    // Navier-Stokes field

    lbeField f;
    
    createLbeField( &mesh, &f, "f", MUST_READ);

    f.update = 1;
    
    /* if(frozen == 0) { f.update = 0; } */


    
    /* // Energy field */

    /* lbeField g; */
    
    /* createLbeField( &mesh, &g, "g"); */

    /* if(ht == 0) { g.update = 0; } */
    
    

    // Initial equilibrium distribution
   
    equilibrium(&mesh, &mfields, &f);
    
    /* equilibrium(&mesh, &mfields, &g); */





    // Update macroscopic interaction force

    mfields.Fi = matrixDoubleAlloc( mesh.mesh.nPoints, 3, -1 );
    
    interForce( &mesh, &mfields );
    
    syncVectorField( &mesh, mfields.Fi );



    /* // Heat source */

    /* heatSource( &mesh, &mfields, &g ); */

    /* syncScalarField( &mesh, g.scalarSource ); */
    
   
    /* if(pid == 0){printf("\n\n");} */








    
    // Advance in time. Collide, stream, update and write
    
    while( updateTime(&mesh.time) ) {


	
    	// Collide f (Navier-Stokes)
	
    	collision( &mesh, &mfields, &f );


		
    	/* // Collide g (Temperature) */

    	/* collision( &mesh, &mfields, &g ); */
	
	
	
    	/* // Stream f */
	
    	/* lbstream( &mesh, &f ); */

	
	
    	/* // Stream g */
	
    	/* lbstream( &mesh, &g ); */


	

    	/* // Apply boundary conditions */
	
    	/* updateBoundaries( &mesh, &mfields, &f ); */
	
    	/* updateBoundaries( &mesh, &mfields, &g ); */


	
	
    	/* // Sync fields */

    	/* if( frozen != 0 ) {  syncPdfField( &mesh, f.value );  } */

    	/* if( ht != 0 ) {  syncPdfField( &mesh, g.value );  } */

	
	
	


    	/* // Update macroscopic density */
	
    	/* macroDensity( &mesh, &mfields, &f ); */


	
	
	
    	/* // Update macroscopic temperature */
	
    	/* if( ht != 0 )     { */

    	/*     heatSource( &mesh, &mfields, &g ); */

    	/*     syncScalarField( &mesh, g.scalarSource ); */

    	/* } */

    	/* macroTemperature( &mesh, &mfields, &g ); */


	
	
    	/* // Update macroscopic velocity */
	
    	/* if( frozen != 0 ) { */

    	/*     interForce( &mesh, &mfields ); */

    	/*     syncVectorField( &mesh, mfields.Fi ); */

    	/* } */

    	/* macroVelocity( &mesh, &mfields, &f ); */


	
	
    	// Write fields
	
    	if( writeFlag(&mesh.time) ) {

	    
    	    if(pid == 0) {
		
    		printf( "Time = %d\n", mesh.time.current );
		
    		printf("Elapsed time = %.2f seconds\n\n", elapsed(&mesh.time) );
		
    	    }


	    
    	    // VTK files
	    
    	    writeMeshToVTK( &mesh, &vtk );

    	    writeScalarToVTK( "rho", mfields.rho, &mesh );

    	    writeScalarToVTK( "T", mfields.T, &mesh );

    	    writeVectorToVTK( "U", mfields.U, &mesh );

    	    writePdfToVTK( "f", f.value, &mesh );

    	    /* writePdfToVTK( "g", g.value, &mesh ); */
    
    	    writeVTKExtra( &mesh, &vtk );

    	    writeMainPvd();


	    
	    
    	}
	

    }



    
    // Print info
    if(pid == 0) {
	
    	printf("\n  Finished in %.2f seconds \n\n", elapsed(&mesh.time) );
	
    }


    
    MPI_Finalize();

    
    return 0;
    
}
