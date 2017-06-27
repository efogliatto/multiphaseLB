#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <latticeMesh.h>
#include <basic.h>
#include <io.h>
#include <latticeModel.h>


void writeLatticeMesh( struct latticeMesh* mesh ) {


    uint i,j;

    // Write files
    char command[100];
    sprintf(command,"mkdir -p processor%d/lattice", mesh->parallel.pid);
    
    int status = system( command );
    if(status) {}


    FILE *outFile;

    
    // Local points

    sprintf(command,"processor%d/lattice/points", mesh->parallel.pid);
    
    outFile = fopen(command,"w");

    fprintf(outFile,"%d\n",mesh->parallel.nlocal);

    for( i = 0 ; i < mesh->parallel.nlocal ; i++ ) {

    	fprintf(outFile,"%d %d %d\n",mesh->mesh.points[i][0],mesh->mesh.points[i][1],mesh->mesh.points[i][2]);

    }
    
    fclose(outFile);



    // Ghost points

    sprintf(command,"processor%d/lattice/ghosts", mesh->parallel.pid);
    
    outFile = fopen(command,"w");

    fprintf(outFile,"%d\n",mesh->parallel.nghosts);

    for( i = mesh->parallel.nlocal ; i < mesh->mesh.nPoints ; i++ ) {

    	fprintf(outFile,"%d %d %d\n",mesh->mesh.points[i][0],mesh->mesh.points[i][1],mesh->mesh.points[i][2]);

    }
    
    fclose(outFile);


    
    
    /* // Neighbours */
    
    /* outFile = fopen("lattice/neighbours","w"); */

    /* for( i = 0 ; i < mesh->nPoints ; i++ ) { */

    /* 	for( j = 0 ; j < mesh->Q ; j++ ) { */

    /* 	    fprintf(outFile,"%d ",mesh->nb[i][j]); */

    /* 	} */

    /* 	fprintf(outFile,"\n"); */

    /* } */

    /* fclose(outFile); */



    


    /* // Boundary */
    /* outFile = fopen("lattice/boundary","w"); */
	
    /* fprintf(outFile,"%d\n\n", mesh->bd.nbd); */

    /* for( i = 0 ; i < mesh->bd.nbd ; i++ ) { */

    /* 	fprintf(outFile,"%s\n",mesh->bd.bdNames[i]); */
	
    /* 	fprintf(outFile,"%d\n",mesh->bd.nbdelem[i]); */

    /* 	for( j = 0 ; j < mesh->bd.nbdelem[i] ; j++ ) { */

    /* 	    fprintf(outFile,"%d\n",mesh->bd.bdPoints[i][j]); */

    /* 	} */

    /* 	fprintf(outFile,"\n"); */
	

    /* } */
	
	
    /* fclose(outFile); */





    /* // Write VTK cells */
    
    /* outFile = fopen("lattice/vtkCells","w"); */
    
    /* fprintf(outFile,"%d %d\n", mesh->ncells, mesh->cellType); */
    
    /* for( i = 0 ; i < mesh->ncells ; i++ ) { */
	
    /* 	for( j = 0 ; j < mesh->cellType ; j++ ) { */
	    
    /* 	    fprintf(outFile,"%d ",mesh->vtkCells[i][j]); */
	    
    /* 	} */
	
    /* 	fprintf(outFile,"\n"); */
	
    /* } */
    
    /* fclose(outFile); */
    







    


    
}
