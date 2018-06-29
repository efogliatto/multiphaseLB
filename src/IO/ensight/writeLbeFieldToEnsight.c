#include <latticeMesh.h>
#include <basic.h>
#include <writeLbeFieldToEnsight.h>
#include <writeScalarToEnsight.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>


void writeLbeFieldToEnsight( char* fname, scalar** field, latticeMesh* mesh ) {


    char* cname;
    
    uint status, k;

    for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	
	status = vstring(&cname, "%s%d", fname, k);

	if(status) {}


	// Count file ocurrences

	DIR *dir;
    
	struct dirent *ent;

	uint fcount = 0;

	char name[256];

	sprintf(name,"lattice.%s",cname);


	if ((dir = opendir (".")) != NULL) {

	    while ((ent = readdir (dir)) != NULL) {
	    
		if(strstr(ent->d_name, name) != NULL) {

		    fcount++;

		}
	    
	    }
	
	    closedir (dir);
	
	}




	// Write field
    
	FILE *outFile;

	char fileName[100];
      

	if( mesh->parallel.pid == 0 ) {

	    sprintf(fileName, "lattice.%s%d", cname, fcount);
	
	    outFile = fopen(fileName, "w");

	    fprintf(outFile, "%s\n", cname);

	    fclose(outFile);

	    fcount++;

	}


	sprintf(fileName, "lattice.%s%d", cname, fcount-1);

	outFile = fopen(fileName, "a");

	fprintf(outFile,"part\n");
	fprintf(outFile,"%10d\n",mesh->parallel.pid+1);
	fprintf(outFile,"coordinates\n");
	
	uint i;
    
	for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {
	
	    fprintf(outFile, "%12.5e\n", field[i][k]);
	
	}


	fclose(outFile);
	
	

    }


    free(cname);
    

}
