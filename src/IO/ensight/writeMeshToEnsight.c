#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <writeMeshToEnsight.h>
#include <basic.h>
#include <vtkInfo.h>
#include <readVTKInfo.h>
#include <updateCaseFile.h>


void writeMeshToEnsight( latticeMesh* mesh ) {

    FILE *outFile;

    char fileName[100];


   
    // Write Mesh
    
    sprintf(fileName, "lattice.geo");


    // Headers first

    if( mesh->parallel.pid == 0 ) {

	    
	// Open File
	    
	outFile = fopen(fileName, "wb");

	testFile(outFile, fileName);
	
	
	// Headers

	char* msg = (char*)malloc( 80*sizeof(char) );


	memset(msg,'\0', 80);	

	sprintf(msg, "C Binary");

	fwrite( msg, sizeof(char), 80, outFile );

	

	memset(msg,'\0', 80);	

	sprintf(msg, "EnSight Model Geometry File");

	fwrite( msg, sizeof(char), 80, outFile );

	
	
	memset(msg,'\0', 80);
	
	sprintf(msg, "EnSight 7.4.1");

	fwrite( msg, sizeof(char), 80, outFile );


	
	memset(msg,'\0', 80);	

	sprintf(msg, "node id assign");

	fwrite( msg, sizeof(char), 80, outFile );
	

	
	memset(msg,'\0', 80);	
	
	sprintf(msg, "element id assign");

	fwrite( msg, sizeof(char), 80, outFile );
	
	

	// Memory release
	
	fclose(outFile);
	
	free(msg);
	

	
	// Create .case file
	
	updateCaseFile( mesh );


    }



    // Points coordinates

    outFile = fopen(fileName, "a");

    testFile(outFile, fileName);




    char* msg = (char*)malloc( 80*sizeof(char) );

    memset(msg,'\0', 80);	

    sprintf(msg, "part");

    fwrite( msg, sizeof(char), 80, outFile );


    int pp = mesh->parallel.pid+1;
    
    fwrite( &pp, sizeof(int), 1, outFile );
    
    



    memset(msg,'\0', 80);	

    sprintf(msg, "Point field");

    fwrite( msg, sizeof(char), 80, outFile );




    memset(msg,'\0', 80);	

    sprintf(msg, "coordinates");

    fwrite( msg, sizeof(char), 80, outFile );


    fwrite( &mesh->mesh.nPoints, sizeof(int), 1, outFile );
    


    // Write mesh points
    
    uint i,j;

    for( j = 0 ; j < 3 ; j++ ) {
	
    	for( i = 0 ; i < mesh->mesh.nPoints ; i++) {

	    float value = (float)mesh->mesh.points[i][j];
	    
	    fwrite( &value, sizeof(float), 1, outFile );

    	}

    }



    // Lattice elements
	
    if( mesh->lattice.model == D2Q9 ) {

	memset(msg,'\0', 80);	

	sprintf(msg, "quad4");

	fwrite( msg, sizeof(char), 80, outFile );
		
        fwrite( &mesh->mesh.ncells, sizeof(int), 1, outFile ); 

    	

    	for( i = 0 ; i < mesh->mesh.ncells ; i++) {

	    int id = mesh->mesh.vtkCells[i][0]+1;
		
	    fwrite( &id, sizeof(int), 1, outFile );	       

	    id = mesh->mesh.vtkCells[i][1]+1;

	    fwrite( &id, sizeof(int), 1, outFile );

	    id = mesh->mesh.vtkCells[i][3]+1;
	    
	    fwrite( &id, sizeof(int), 1, outFile );

	    id = mesh->mesh.vtkCells[i][2]+1;

	    fwrite( &id, sizeof(int), 1, outFile );	    

    	}

    }

    else {

	if( mesh->lattice.model == D3Q15 ) {

	    memset(msg,'\0', 80);	

	    sprintf(msg, "hexa8");

	    fwrite( msg, sizeof(char), 80, outFile );
		
	    fwrite( &mesh->mesh.ncells, sizeof(int), 1, outFile ); 

    	

	    for( i = 0 ; i < mesh->mesh.ncells ; i++) {

		int id = mesh->mesh.vtkCells[i][0]+1;
		
		fwrite( &id, sizeof(int), 1, outFile );	       

		id = mesh->mesh.vtkCells[i][1]+1;

		fwrite( &id, sizeof(int), 1, outFile );

		id = mesh->mesh.vtkCells[i][3]+1;
	    
		fwrite( &id, sizeof(int), 1, outFile );

		id = mesh->mesh.vtkCells[i][2]+1;

		fwrite( &id, sizeof(int), 1, outFile );




		id = mesh->mesh.vtkCells[i][4]+1;
		
		fwrite( &id, sizeof(int), 1, outFile );	       

		id = mesh->mesh.vtkCells[i][5]+1;

		fwrite( &id, sizeof(int), 1, outFile );

		id = mesh->mesh.vtkCells[i][7]+1;
	    
		fwrite( &id, sizeof(int), 1, outFile );

		id = mesh->mesh.vtkCells[i][6]+1;

		fwrite( &id, sizeof(int), 1, outFile );
		

	    }

	}

    }
    

    fclose(outFile);

    free(msg);


}


/* // ASCII Version */

/* void writeMeshToEnsight( latticeMesh* mesh ) { */

/*     FILE *outFile; */

/*     char fileName[100]; */


   
/*     // Write Mesh */
    
/*     sprintf(fileName, "lattice.geo"); */


/*     // Headers first */

/*     if( mesh->parallel.pid == 0 ) { */

	    
/* 	// Open File */
	    
/* 	outFile = fopen(fileName, "w"); */

/* 	testFile(outFile, fileName); */
	
	
/* 	// Headers */

/* 	fprintf(outFile,"EnSight Model Geometry File\n"); */
/* 	fprintf(outFile,"EnSight 7.4.1\n"); */
/* 	fprintf(outFile,"node id assign\n"); */
/* 	fprintf(outFile,"element id assign\n"); */
/* 	/\* fprintf(outFile,"extents\n"); *\/ */
/* 	/\* fprintf(outFile," 0.00000e+00 1.00000e+00\n"); *\/ */
/* 	/\* fprintf(outFile," 0.00000e+00 1.00000e+00\n"); *\/ */
/* 	/\* fprintf(outFile," 0.00000e+00 0.00000e+00\n"); *\/ */
	    

/* 	fclose(outFile); */

	

/* 	// Create .case file */
	
/* 	updateCaseFile( mesh );	 */

/*     } */



/*     // Points coordinates */

/*     outFile = fopen(fileName, "a"); */

/*     testFile(outFile, fileName); */

/*     fprintf(outFile,"part\n"); */

/*     fprintf(outFile,"%10d\n",mesh->parallel.pid+1); */

/*     fprintf(outFile,"Point field\n"); */

/*     fprintf(outFile,"coordinates\n"); */

/*     fprintf(outFile,"%10d\n",mesh->mesh.nPoints); */


    
/*     uint i,j; */

/*     for( j = 0 ; j < 3 ; j++ ) { */
	
/* 	for( i = 0 ; i < mesh->mesh.nPoints ; i++) { */

/* 	    fprintf(outFile,"%12.5e\n",(scalar)mesh->mesh.points[i][j]);     */

/* 	} */

/*     } */



/*     // Lattice elements */
	
/*     if( mesh->lattice.model == D2Q9 ) { */

/* 	fprintf(outFile,"quad4\n"); */

/* 	fprintf(outFile,"%10d\n", mesh->mesh.ncells); */

/* 	for( i = 0 ; i < mesh->mesh.ncells ; i++) { */
	    
/* 	    fprintf(outFile,"%10d ",mesh->mesh.vtkCells[i][0]+1); */

/* 	    fprintf(outFile,"%10d ",mesh->mesh.vtkCells[i][1]+1); */

/* 	    fprintf(outFile,"%10d ",mesh->mesh.vtkCells[i][3]+1); */

/* 	    fprintf(outFile,"%10d\n",mesh->mesh.vtkCells[i][2]+1);	     */

/* 	} */

/*     } */


/*     fclose(outFile); */


/* } */
