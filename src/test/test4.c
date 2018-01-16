/*

  Multiphase solver with heat transfer

 */


#include <io.h>
#include <latticeModel.h>
#include <basic.h>

#include <mpi.h>
#include <macroFields.h>
#include <vtkInfo.h>
#include <finiteDifference.h>


int main( int argc, char **argv ) {


   
    int pid, world;
    
    // Initialize mpi

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&pid);

    MPI_Comm_size(MPI_COMM_WORLD,&world);
    

    
    // Simulation properties
    
    struct latticeMesh mesh = readLatticeMesh( pid );    

    mesh.lattice = setLatticeInfo();

    mesh.EOS = readEOSInfo();

    struct vtkInfo vtk = readVTKInfo();
    

    
    

    // Macroscopic fields
    
    struct macroFields mfields;

    uint status;
    

    
    // Scalar field

    if(pid == 0) {  printf("\nReading field scalar\n");  }
    
    status = readScalarField( &mesh, &mfields.rho, "scalar");

    if( status == 0 ) {

    	printf("\n   [ERROR]  Unable to read field scalar\n\n");

    	exit(1);

    }



    
    // Gradient

    if(pid == 0) {  printf("\nReading field grad\n");  }
    
    status = readVectorField( &mesh, &mfields.U, 3, "grad");

    if( status == 0 ) {

    	printf("\n   [ERROR]  Unable to read field grad\n\n");

    	exit(1);

    }
    

    
    // Divergence

    if(pid == 0) {  printf("\nReading field div\n");  }
    
    status = readScalarField( &mesh, &mfields.T, "div");

    if( status == 0 ) {

    	printf("\n   [ERROR]  Unable to read field div\n\n");

    	exit(1);

    }
    
   
    if(pid == 0){printf("\n\n");}








    
    // write
    
    while( updateTime(&mesh.time) ) {



	// Compute gradient of scalar field

	unsigned int i;

	for( i = 0 ; i < mesh.parallel.nlocal ; i++ ) {

	    /* scalarGradient( mfields.U[i], mfields.rho, &mesh, i);  */

	    mfields.U[i][0] = mesh.mesh.points[i][0];
	    
	    mfields.U[i][1] = mesh.mesh.points[i][1];

	}


	// Compute divergence of vector field

	for( i = 0 ; i < mesh.parallel.nlocal ; i++ ) {

	    mfields.T[i] = vectorDivergence( mfields.U, &mesh, i );

	}

	
	
    	// Write fields
	
    	if( writeFlag(&mesh.time) ) {

	    
    	    if(pid == 0) {
		
    		printf( "Time = %d\n", mesh.time.current );	       
		
    	    }


	    
    	    // VTK files
	    
    	    writeMeshToVTK( &mesh, &vtk );

    	    writeScalarToVTK( "scalar", mfields.rho, &mesh );

    	    writeScalarToVTK( "div", mfields.T, &mesh );

    	    writeVectorToVTK( "grad", mfields.U, &mesh );
    
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
