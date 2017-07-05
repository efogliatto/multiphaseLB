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
    
    

   
   
    if(pid == 0){printf("\n\n");}




    {

	unsigned int i, j;

	for( i = 0 ; i < mesh.parallel.nlocal ; i++) {

	    for( j = 0 ; j < mesh.mesh.Q ; j++ ) {

		f.value[i][j] = i;

	    }

	}
	
    }
    




    
    // Advance in time. Collide, stream, update and write
    
    while( updateTime(&mesh.time) ) {

	
	syncPdfField( &mesh, f.value );

	
	/* if( pid == 1 ) { */

	/*     unsigned int ii, jj, kk, id; */

	/*     for( jj = 0 ; jj < world ; jj++ ) { */

	/* 	printf("%d  ",jj); */

	/* 	for( ii = 0 ; ii < mesh.parallel.shared[jj] ; ii++) { */

	/* 	    for( kk = 0 ; kk < mesh.mesh.Q ; kk++ ) { */

	/* 		id = ii*mesh.mesh.Q + kk; */
			
	/* 		printf(" %.0f", mesh.parallel.sbuf[jj][id]); */

	/* 	    } */

		    

	/* 	} */

	/* 	printf("\n"); */

	/*     } */


	/*     printf("\n\n"); */
	    

	/*     for( jj = 0 ; jj < world ; jj++ ) { */

	/* 	printf("%d  ",jj); */

	/* 	for( ii = 0 ; ii < mesh.parallel.shared[jj] ; ii++) { */

	/* 	    for( kk = 0 ; kk < mesh.mesh.Q ; kk++ ) { */

	/* 		id = ii*mesh.mesh.Q + kk; */
			
	/* 		printf(" %.0f", mesh.parallel.rbuf[jj][id]); */

	/* 	    } */

		    

	/* 	} */

	/* 	printf("\n"); */

	/*     } */

	/* } */

	
	
    	// Write fields
	
    	if( writeFlag(&mesh.time) ) {

	        
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



    


    
    MPI_Finalize();

    
    return 0;
    
}
