/*

  latticeBox2D

  lattice generation in a 2D Box

*/

/* #include <periodicX.h> */
/* #include <periodicY.h> */

#include <io.h>
#include <latticeModel.h>
#include <basic.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;


void periodicX( int** neigh, unsigned int nx, unsigned int ny, unsigned int Q, int** bmap, int* btid );
void periodicY( int** neigh, unsigned int nx, unsigned int ny, unsigned int Q, int** bmap, int* btid );
void periodicXY( int** neigh, unsigned int nx, unsigned int ny, unsigned int Q, int** bmap, int* btid );

int main(int argc, char** argv) {

    
    printf("\n\n   LATTICE MESH GENERATION\n\n");



    
    // Basic lattice properties
    

    // Lattice size
    uint nx = (uint)lookUpDoubleEntry("properties/latticeProperties","Nx",-1);
    uint ny = (uint)lookUpDoubleEntry("properties/latticeProperties","Ny",-1);

    // Lattice model
    char lbm[100];
    lookUpStringEntry("properties/latticeProperties","LBModel",lbm);

    // Boundary type
    char bdType[100];
    lookUpStringEntry("properties/latticeProperties","boundaryType",bdType);
    



    

    // ******************************************************************** //
    //                         Points inside geometry                       //
    // ******************************************************************** //

    
    printf("Adding points to lattice\n\n");

    int** meshPoints = matrixIntAlloc(nx*ny,3,0);

        
    // Move over indices

    int i,j;

    for( j = 0 ; j < ny ; j++) {
	
    	for( i = 0 ; i < nx ; i++) {
			    
    	    meshPoints[i+j*nx][0] = i;
	    meshPoints[i+j*nx][1] = j;
		
    	}
    }




    
    

    // ******************************************************************** //
    //                             Neighbours                               //
    // ******************************************************************** //

    
    printf("Computing neighbour indices\n\n");

    
    // Lattice velocities
    int** velocities = latticeVelocities(lbm);
    int* rev = latticeReverseDir(lbm);
    
    // Create and resize neighbour matrix
    int** neigh = matrixIntAlloc(nx*ny,latticeQ(lbm),-1);
    

    

    // Check for neighbouring
    // There is no need to iterate over all points to look for a neighbour. Given a lattice velocity vector (x,y,z), the neighbour of a point
    // p with index pointId is at most at pointId + x + (y*Nx).

    
    // Internal points first

    int pointId, velId;
    
    for( j = 1 ; j < (ny-1) ; j++) {
	
    	for( i = 1 ; i < (nx-1) ; i++) {

	    pointId = i+j*nx;


	    // Iterate on velocities
	    for( velId = 0 ; velId < latticeQ(lbm) ; velId++ ) {

		neigh[pointId][velId] = pointId   +   velocities[ rev[velId] ][0]   +   velocities[ rev[velId] ][1] * nx;

	    }
	    
	}

    }

    

    // For boundary nodes, check neighbouring using distance to point

    for( j = 0 ; j < ny ; j+=(ny-1)) {
	
	for( i = 0 ; i < nx ; i++) {

	    pointId = i+j*nx;

	    // Iterate on velocities
	    for( velId = 0 ; velId < latticeQ(lbm) ; velId++ ) {

		int newId = pointId   +   velocities[ rev[velId] ][0]   +   velocities[ rev[velId] ][1] * nx;

		if( newId >= 0   &&   newId <= nx*ny-1 ) {

		    if ( (  abs( meshPoints[pointId][0] - meshPoints[newId][0] ) <= 1  )   &&   (  abs( meshPoints[pointId][1] - meshPoints[newId][1] ) <= 1  )  ) {
	    
			neigh[pointId][velId] = newId;

		    }

		}

	    }
	    
	}

    }


    for( j = 1 ; j < ny-1 ; j++ ) {
	
	for( i = 0 ; i < nx ; i+=(nx-1)) {

	    pointId = i+j*nx;

	    // Iterate on velocities
	    for( velId = 0 ; velId < latticeQ(lbm) ; velId++ ) {

		int newId = pointId   +   velocities[ rev[velId] ][0]   +   velocities[ rev[velId] ][1] * nx;

		if( newId >= 0   &&   newId <= nx*ny-1 ) {

		    if ( (  abs( meshPoints[pointId][0] - meshPoints[newId][0] ) <= 1  )   &&   (  abs( meshPoints[pointId][1] - meshPoints[newId][1] ) <= 1  )  ) {
	    
			neigh[pointId][velId] = newId;

		    }

		}

	    }
	    
	}

    }
    


    	




    

	    
    
    // ******************************************************************** //
    //                             Boundary                                 //
    // ******************************************************************** //

    printf("Computing boundary nodes\n\n");

    char bdmap[4][100];
    sprintf(bdmap[0],"X0");
    sprintf(bdmap[1],"X1");
    sprintf(bdmap[2],"Y0");
    sprintf(bdmap[3],"Y1");

    int** bmap = matrixIntAlloc(4,nx+ny,0);;
    int btid[4];

    // Assign points on boundary based on bdType

    // Generic
    if( strcmp(bdType,"generic") == 0) { }


    // periodicX
    else {

	if( strcmp(bdType,"periodicX")  == 0 ) {

	    periodicX( neigh, nx, ny, latticeQ(lbm), bmap, btid );

	}


	// periodicY
	else {

	    if( strcmp(bdType,"periodicY")  == 0 ) {

		periodicY( neigh, nx, ny, latticeQ(lbm), bmap, btid );

	    }


	    // periodicXY
	    else {

		if( strcmp(bdType,"periodicXY")  == 0 ) {

		    periodicXY( neigh, nx, ny, latticeQ(lbm), bmap, btid );

		}

		else {

		    printf("[ERROR]   Unrecognized boundary type %s\n\n", bdType);
		    exit(0);

		}
	
	    }	    
	
	}	
	
    }
    




	    

    


    /* // 	    // ******************************************************************** // */
    /* // 	    //                             VTK Cells                                // */
    /* // 	    // ******************************************************************** // */

    /* // 	    cout << "Creating VTK Cells" << endl << endl; */
    
    /* // 	    vector< vector<uint> > vtkCells; */

    /* // 	    if(lbm->D() == 2) { */


    /* // 	    	// Iterate on points */
    /* // 	    	for(uint pointId = 0 ; pointId < meshPoints.size() ; pointId++) { */
    /* // 	    	    // for(uint pointId = 0 ; pointId < 1 ; pointId++) { */

    /* // 	    	    vector<uint> id; */
    /* // 	    	    id.push_back( pointId ); */

    /* // 	    	    uint pt = pointId; */

    /* // 	    	    for(uint velId = 1 ; velId < 4 ; velId ++) { */
    /* // 	    		int aux = neigh[pt][lbm->reverse(velId)]; */
    /* // 	    		if( aux != -1 ) { */
    /* // 	    		    pt = aux; */
    /* // 	    		    id.push_back(pt); */
    /* // 	    		} */
    /* // 	    	    } */

    /* // 	    	    if (id.size() == 4) { */
    /* // 	    		uint a = id[3]; */
    /* // 	    		id[3] = id[2]; */
    /* // 	    		id[2] = a; */
    /* // 	    		vtkCells.push_back(id); */
    /* // 	    	    } */
	
    /* // 	    	} */

	
    /* // 	    } */







    


	    


    // ******************************************************************** //
    //                             Writing                                  //
    // ******************************************************************** //
    
    printf("Writting Mesh\n\n");


    // Write files
    int status = system( "mkdir -p lattice" );
    if(status) {}

    
    FILE *outFile;

    
    // Points
    outFile = fopen("lattice/points","w");   
    fprintf(outFile,"%d\n",nx*ny);
    for( i = 0 ; i < nx*ny ; i++ ) { fprintf(outFile,"%d %d 0\n",meshPoints[i][0],meshPoints[i][1]);   }
    fclose(outFile);


    // Neighbours
    outFile = fopen("lattice/neighbours","w");   
    for( i = 0 ; i < nx*ny ; i++ ) {
	for( j = 0 ; j < latticeQ(lbm) ; j++ ) {
	    fprintf(outFile,"%d ",neigh[i][j]);
	}
	fprintf(outFile,"\n");
    }
    fclose(outFile);    
      


    // Boundary
    outFile = fopen("lattice/boundary","w");
    if( strcmp(bdType,"periodicXY")  == 0 ) {
	
	fprintf(outFile,"0\n");
	
    }
    else {
	
	fprintf(outFile,"4\n\n");

	for( i = 0 ; i < 4 ; i++ ) {

	    fprintf(outFile,"%s\n",bdmap[i]);
	    fprintf(outFile,"%d\n",btid[i]);

	    for( j = 0 ; j < btid[i] ; j++ ) {

		fprintf(outFile,"%d\n",bmap[i][j]);

	    }

	    fprintf(outFile,"\n");
	

	}
	
    }
	
    fclose(outFile);




    /* // 	    // Write VTK cells */

    /* // 	    filename = folder.str() + "vtkCells"; */
    /* // 	    outFile.open( filename.c_str() ); */
    /* // 	    if( !outFile.is_open() ){ */
    /* // 	    	cout << "Cant't open file " << filename << endl; */
    /* // 	    	exit(1); */
    /* // 	    } */

    /* // 	    // Total number of cells */
    /* // 	    outFile << vtkCells.size() << endl; */
	
    /* // 	    for(vector< vector<uint> >::const_iterator cell = vtkCells.begin() ; cell != vtkCells.end() ; cell++) { */
    /* // 	    	outFile << cell->size() << "  "; */
    /* // 	    	for(uint cellId = 0 ; cellId < cell->size() ; cellId++) { */
    /* // 	    	    outFile << cell->at(cellId) << "  "; */
    /* // 	    	} */
    /* // 	    	outFile << endl; */
    /* // 	    } */
	
    /* // 	    outFile.close();     */



	
	    
	    
    /* // 	} */
	



    /* // } */
    /* //  */

    return 0;

}
