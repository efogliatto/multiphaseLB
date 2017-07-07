/*

  Multiphase solver with heat transfer

 */


#include <io.h>
#include <latticeModel.h>
#include <basic.h>

#include <mpi.h>
#include <macroFields.h>
#include <vtkInfo.h>
#include <generalLbe.h>
#include <pseudoPot.h>



int main( int argc, char **argv ) {



    // Check for arguments
    unsigned int ht = 1, frozen = 1;
    {
	unsigned int arg;
	for( arg = 0 ; arg < argc ; arg++) {

	    if ( strcmp("--noHeatTransfer", argv[arg]) == 0 ) {
		ht = 0;
	    }

	    else {

		if ( strcmp("--frozenFlow", argv[arg]) == 0 ) {
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
    
    struct latticeMesh mesh = readLatticeMesh( pid );

    mesh.lattice = setLatticeInfo();

    mesh.EOS = readEOSInfo();

    struct vtkInfo vtk = readVTKInfo();
    

    
    

    // Macroscopic fields
    
    struct macroFields mfields;

    uint status;
    

    
    // Density

    if(pid == 0) {  printf("\nReading field rho\n");  }
    
    status = readScalarField( &mesh, &mfields.rho, "rho");

    if( status == 0 ) {

    	printf("\n   [ERROR]  Unable to read field rho\n\n");

    	exit(1);

    }



    
    // Velocity

    if(pid == 0) {  printf("\nReading field U\n");  }
    
    status = readVectorField( &mesh, &mfields.U, 3, "U");

    if( status == 0 ) {

    	printf("\n   [ERROR]  Unable to read field U\n\n");

    	exit(1);

    }
    

    
    // Temperature

    if(pid == 0) {  printf("\nReading field T\n");  }
    
    status = readScalarField( &mesh, &mfields.T, "T");

    if( status == 0 ) {

    	printf("\n   [ERROR]  Unable to read field T\n\n");

    	exit(1);

    }



    


    // LBE fields

    // Navier-Stokes field

    if(pid == 0) {  printf("\nReading field f\n");  }

    struct lbeField f;
    
    status = readLbeField( &mesh, &f, "f");

    if( status == 0 ) {

    	printf("\n   [ERROR]  Unable to read field f\n\n");

    	exit(1);

    }


    
    // Energy field

    if(pid == 0) {  printf("\nReading field g\n");  }

    struct lbeField g;
    
    status = readLbeField( &mesh, &g, "g");

    if( status == 0 ) {

    	printf("\n   [ERROR]  Unable to read field g\n\n");

    	exit(1);

    }
    
    

    // Initial equilibrium distribution

    // f
    
    if( frozen != 0 ) {  equilibrium(&mesh, &mfields, &f); }

	    
    // g
    
    if( ht != 0 ) {  equilibrium(&mesh, &mfields, &g); }





    // Update macroscopic interaction force

    mfields.Fi = matrixDoubleAlloc( mesh.mesh.nPoints, 3, -1 );
    
    interForce( &mesh, &mfields );
    
    syncVectorField( &mesh, mfields.Fi );
    

    
   
    if(pid == 0){printf("\n\n");}








    
    // Advance in time. Collide, stream, update and write
    
    while( updateTime(&mesh.time) ) {

	
    	// Collide f (Navier-Stokes)

    	if( frozen != 0 ) {  collision( &mesh, &mfields, &f );  }
	

	
    	// Collide g (Temperature)

    	if( ht != 0 ) {  collision( &mesh, &mfields, &g );  }


	
	
    	// Stream f
	
    	if( frozen != 0 ) {  lbstream( &mesh, &f );  }


	
    	// Stream g
	
    	if( ht != 0 ) {  lbstream( &mesh, &g );  }



	
    	// Sync fields

    	if( frozen != 0 ) {  syncPdfField( &mesh, f.value );  }

    	if( ht != 0 ) {  syncPdfField( &mesh, g.value );  }


	


    	// Update macroscopic density
	
    	if( frozen != 0 ) {  macroDensity( &mesh, &mfields, &f ); }
	
	
    	// Update macroscopic temperature
	
    	if( ht != 0 )     {  macroTemperature( &mesh, &mfields, &g );    }


	// Update force
	
    	interForce( &mesh, &mfields );

	syncVectorField( &mesh, mfields.Fi ); 
	
	
    	// Update macroscopic velocity
	
    	if( frozen != 0 ) {  macroVelocity( &mesh, &mfields, &f ); }
	

	

	

	
    	// Apply boundary conditions
	
    	if( frozen != 0 ) {  updateBoundaries( &mesh, &mfields, &f );  }
	
    	if( ht != 0 )     {  updateBoundaries( &mesh, &mfields, &g );  }


	// F is not sync yet. Boundary conditions that are already implemented don't need another sync.
	// Remember that ghost nodes at boundary are updated
    	/* syncPdfField( &mesh, f.value ); */

    	if( ht != 0 ) {  syncPdfField( &mesh, g.value );  }

	
    	if( frozen != 0 ) {  updateBdElements( &mesh, &mfields, &f );  }
	
    	if( ht != 0 )     {  updateBdElements( &mesh, &mfields, &g );  }


    	/* updateBdForce( &mesh, &mfields ); */


	
	
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

    	    writePdfToVTK( "g", g.value, &mesh );
    
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
