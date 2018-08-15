/*

  Multiphase solver with heat transfer

 */


#include <io.h>
#include <latticeModel.h>
#include <basic.h>
#include <mpi.h>
#include <generalLbe.h>
#include <pseudoPot.h>
#include <omp.h>
#include <checkMpArgs.h>



int main( int argc, char **argv ) {



    // Check for arguments

    mpOptions mp = checkMpArgs( argc, argv );
    
    

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


    
    
    // Velocity

    createVectorField( &mesh, &mfields.U, 3, "U", MUST_READ);
    

    
    // Temperature

    createScalarField( &mesh, &mfields.T, "T", MUST_READ);



    // Pressure

    createScalarField( &mesh, &mfields.p, "p", MUST_READ);
    
    


    // LBE fields

    // Navier-Stokes field

    lbeField f;
    
    createLbeField( &mesh, &f, "f", MUST_READ);

    if(mp.frozen == 0) { f.update = 0; }


    
    // Energy field

    lbeField g;
    
    createLbeField( &mesh, &g, "g", MUST_READ);

    if(mp.ht == 0) { g.update = 0; }
    
    

    // Initial equilibrium distribution
   
    equilibrium(&mesh, &mfields, &f);
    
    equilibrium(&mesh, &mfields, &g);





    // Update macroscopic interaction force

    mfields.Fi = matrixDoubleAlloc( mesh.mesh.nPoints, 3, -1 );
    
    interForce( &mesh, &mfields );
    
    syncVectorField( &mesh, mfields.Fi );


    

    // Heat source

    heatSource( &mesh, &mfields, &g );

    syncScalarField( &mesh, g.scalarSource );
    
   
    if(pid == 0){printf("\n\n");}



    
    // Advance in time. Collide, stream, update and write
    
    while( updateTime(&mesh.time) ) {


	    
	// Collide f (Navier-Stokes)
	
	collision( &mesh, &mfields, &f );


		
	// Collide g (Temperature)

	collision( &mesh, &mfields, &g );
	
	
	
	// Stream f
	
	lbstream( &mesh, &f );

	
	
	// Stream g
	
	lbstream( &mesh, &g );


	

	// Apply boundary conditions
	
	updateBoundaries( &mesh, &mfields, &f );
	
	updateBoundaries( &mesh, &mfields, &g );



	// Only rho

	{

	    // Send pdf fields

	    if( mp.frozen != 0 ) {  sendPdfField( &mesh, &f );  }

	    if( mp.ht != 0 ) {  sendPdfField( &mesh, &g );  }

	    
	    
	    // Update macroscopic density
	
	    macroDensity( &mesh, &mfields, &f, 0, mesh.parallel.nlocal );



	    if( mp.frozen != 0 ) {  recvPdfField( &mesh, &f );  }

	    if( mp.ht != 0 ) {  recvPdfField( &mesh, &g );  }

	    
	    
	    // Update macroscopic density
	
	    macroDensity( &mesh, &mfields, &f, mesh.parallel.nlocal, mesh.mesh.nPoints );

	    
	    
	
	
	    // Update macroscopic temperature
	
	    if( mp.ht != 0 )     {

		heatSource( &mesh, &mfields, &g );

		syncScalarField( &mesh, g.scalarSource );

	    }

	    macroTemperature( &mesh, &mfields, &g, 0, mesh.mesh.nPoints );


	
	
	    // Update macroscopic velocity
	
	    if( mp.frozen != 0 ) {

		interForce( &mesh, &mfields );

		syncVectorField( &mesh, mfields.Fi );

	    }

	    macroVelocity( &mesh, &mfields, &f, 0, mesh.mesh.nPoints );
	    
	    

	}






	

	/* // Levels */

	/* { */
	
	/*     // Send pdf fields */

	/*     if( mp.frozen != 0 ) {  sendPdfField( &mesh, &f );  } */

	/*     if( mp.ht != 0 ) {  sendPdfField( &mesh, &g );  } */

	
		


	/*     // Update macroscopic density. Level 1-4 */

	/*     uint lv; */

	/*     for( lv = 1 ; lv <= 4 ; lv++ )	{ */
	    
	/* 	macroDensityInLevel( &mesh, &mfields, &f, lv ); */

	/*     } */

	

	/*     // Update macroscopic heat source and temperature. Level 2-4 */

	/*     for( lv = 2 ; lv <= 4 ; lv++ )	{ */

	/* 	if( mp.ht != 0 ) { heatSourceInLevel( &mesh, &mfields, &g, lv ); } */

	/* 	macroTemperatureInLevel( &mesh, &mfields, &g, lv ); */

	/*     } */




	/*     // Update macroscopic interaction force and velocity. Level 3-4 */

	/*     for( lv = 3 ; lv <= 4 ; lv++ )	{ */

	/* 	if( mp.frozen != 0 ) { interForceInLevel( &mesh, &mfields, lv ); } */

	/* 	macroVelocityInLevel( &mesh, &mfields, &f, lv ); */


	/*     } */
	
	


	/*     // Finish f and g sync. */

	/*     if( mp.frozen != 0 ) {  recvPdfField( &mesh, &f );  } */

	/*     if( mp.ht != 0 ) {  recvPdfField( &mesh, &g );  } */




	/*     // Update macroscopic density. Level 0 */

	/*     macroDensityInLevel( &mesh, &mfields, &f, 0 ); */


	

	/*     // Update macroscopic heat source. Level 1 */

	/*     if( mp.ht != 0 ) { */

	/* 	heatSourceInLevel( &mesh, &mfields, &g, 1 ); */

	/* 	syncScalarField( &mesh, g.scalarSource ); */

	/*     } */



	/*     // Update macroscopic temperature. Level 0-1 */

	/*     for( lv = 0 ; lv <= 1 ; lv++ )	{ */

	/* 	macroTemperatureInLevel( &mesh, &mfields, &g, lv ); */

	/*     } */
	

	

	/*     // Update macroscopic interaction force and velocity. Level 1-2 */

	/*     for( lv = 1 ; lv <= 2 ; lv++ )	{ */

	/* 	if( mp.frozen != 0 ) { interForceInLevel( &mesh, &mfields, lv ); } */

	/* 	syncVectorField( &mesh, mfields.Fi ); */

	/*     } */
	

	
	/*     // Update macroscopic velocity. Level 0-2 */

	/*     for( lv = 0 ; lv <= 2 ; lv++ )	{ */

	/* 	macroVelocityInLevel( &mesh, &mfields, &f, lv ); */

	/*     } */


	/* } */
	

















	
	
    	// Write fields
	
    	if( writeFlag(&mesh.time) ) {

	    
    	    if(pid == 0) {
		
    		printf( "Time = %d\n", mesh.time.current );
		
    		printf("Elapsed time = %.2f seconds\n\n", elapsed(&mesh.time) );
		
    	    }


	    
	    // Update pressure

	    macroPressure( &mesh, &mfields, &f );

	    syncScalarField( &mesh, mfields.p );


	    // Update average density
	    
	    mesh.EOS.rho_0 = averageScalarField(&mesh, mfields.rho);


	    
    	    // Write 

	    if(mesh.time.data == pvtu) {
	    
		writeMeshToVTK( &mesh, &vtk );

	    }

	    if(mesh.time.data == ensight) {

		updateCaseFile(&mesh);

		MPI_Barrier(MPI_COMM_WORLD);

	    }	    

    	    writeScalarField( "rho", mfields.rho, &mesh );

    	    writeScalarField( "T", mfields.T, &mesh );

    	    writeScalarField( "p", mfields.p, &mesh );  

    	    writeVectorField( "U", mfields.U, &mesh, 3 );

    	    writeVectorField( "f", f.value, &mesh, mesh.lattice.Q );

    	    writeVectorField( "g", g.value, &mesh, mesh.lattice.Q );


	    if(mesh.time.data == pvtu) {
	    
		writePvtuExtra( &mesh, &vtk );

		writeMainPvd();

	    }


	    
	    
    	}
	

    }


    /* { */

    /* 	uint ii; */

    /* 	for( ii = 1 ; ii < mesh.parallel.nlocal ; ii+=3 ) { */

    /* 	    printf(  "%d %g %g %g %g\n", mesh.mesh.points[ii][1], */
    /* 		     mfields.Fi[ii][1], */
    /* 		     p_eos(&mesh.EOS, mfields.rho[ii], mfields.T[ii]), */
    /* 		     mfields.rho[ii], */
    /* 		     potential( &mesh, mfields.rho[ii], mfields.T[ii] )); */

    /* 	} */

    /* } */

    
    // Print info
    if(pid == 0) {
	
    	printf("\n  Finished in %.2f seconds \n\n", elapsed(&mesh.time) );
	
    }


    
    MPI_Finalize();

    
    return 0;
    
}
