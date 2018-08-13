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
    	printf("     o<----o---->o       Two Phases - Lattice-Boltzmann solver with heat transfer. Fixed pseudopotential model\n");
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




    // Execution time

    double ctime[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    double start,end;

    

    
    // Advance in time. Collide, stream, update and write
    
    while( updateTime(&mesh.time) ) {


	start = MPI_Wtime();
	
	    
	// Collide f (Navier-Stokes)
	
	collision( &mesh, &mfields, &f );


		
	// Collide g (Temperature)

	collision( &mesh, &mfields, &g );
	
	

	end = MPI_Wtime();

	ctime[0] += end-start;
	

	
	// Stream f
	
	lbstream( &mesh, &f );

	
	
	// Stream g
	
	lbstream( &mesh, &g );


	
	start = MPI_Wtime();

	ctime[1] += start - end;

	

	// Apply boundary conditions
	
	updateBoundaries( &mesh, &mfields, &f );
	
	updateBoundaries( &mesh, &mfields, &g );




	end = MPI_Wtime();

	ctime[2] += end - start;
	
	
	// Sync fields

	/* if( mp.frozen != 0 ) {  syncPdfField( &mesh, f.value );  } */

	/* if( mp.ht != 0 ) {  syncPdfField( &mesh, g.value );  } */

	if( mp.frozen != 0 ) {  sendPdfField( &mesh, &f );  }

	if( mp.ht != 0 ) {  sendPdfField( &mesh, &g );  }

	
	
	start = MPI_Wtime();

	ctime[3] += start - end;
	



	// Update macroscopic density
	
	/* macroDensity( &mesh, &mfields, &f, 0, mesh.mesh.nPoints ); */

	macroDensity( &mesh, &mfields, &f, 0, mesh.parallel.nlocal );              
	


	end = MPI_Wtime();

	ctime[4] += end - start;




	// Receive buffer and finish macro update
	
	if( mp.frozen != 0 ) {  recvPdfField( &mesh, &f );  }

	if( mp.ht != 0 ) {  recvPdfField( &mesh, &g );  }	

       
	
	start = MPI_Wtime();

	ctime[5] += start - end;


	
	
	macroDensity( &mesh, &mfields, &f, mesh.parallel.nlocal, mesh.mesh.nPoints );

	end = MPI_Wtime();

	ctime[6] += end - start;


	
	
	
	// Update macroscopic temperature
	
	if( mp.ht != 0 )     {

	    heatSource( &mesh, &mfields, &g );

	    syncScalarField( &mesh, g.scalarSource );

	}

	macroTemperature( &mesh, &mfields, &g, 0, mesh.mesh.nPoints );



	start = MPI_Wtime();

	ctime[7] += start - end;
	

	
	// Update macroscopic velocity
	
	if( mp.frozen != 0 ) {

	    interForce( &mesh, &mfields );

	    syncVectorField( &mesh, mfields.Fi );

	}

	macroVelocity( &mesh, &mfields, &f, 0, mesh.mesh.nPoints );
	    


	end = MPI_Wtime();

	ctime[8] += end - start;
	
	
	
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



    
    // Print info
    if(pid == 0) {
	
    	printf("\n  Finished in %.2f seconds \n\n", elapsed(&mesh.time) );
	
    }


    {

	double commTime[10];
	
	uint i;

	for( i = 0 ; i < 10 ; i++) {
	    
	    MPI_Allreduce(&ctime[i], &commTime[i], 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	    if(pid == 0) {
	
		printf("Comm %i: %.2f\n", i, commTime[i]/world );
	
	    }
	    
	}

    }


    
    MPI_Finalize();

    
    return 0;
    
}
