#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void writeMainPvd() {

    
    uint* tSteps;

    int status,aux;

    uint nt = 0;
    

    
    // List time folders

    DIR           *d;
	
    struct dirent *dir;
	
    d = opendir(".");
	
    if (d) {
	    
	while ((dir = readdir(d)) != NULL)  {
	    
	    status = sscanf(dir->d_name,"%d",&aux);

	    if( status != 0 ) {
	    
	    	nt++;

	    }
		    

	}

    }



    // Resize time array and copy values

    tSteps = (uint*)malloc( nt * sizeof(uint) );

    nt = 0;
    
    d = opendir(".");
	
    if (d) {
	    
	while ((dir = readdir(d)) != NULL)  {
	    
	    status = sscanf(dir->d_name,"%d",&aux);

	    if( status != 0 ) {

		tSteps[nt] = aux;
		
	    	nt++;

	    }
		    

	}

    }



    

    // Sort time array
    {
	
	int i, j, temp;
	
	for (i = 0; i < (nt-1); ++i) {
	    
	    for (j = 0; j < (nt-1) - i; ++j )  {
		
		if (tSteps[j] > tSteps[j+1])  {
		    
		    temp = tSteps[j+1];
		    
		    tSteps[j+1] = tSteps[j];
		    
		    tSteps[j] = temp;
		    
		}
		
	    }
	    
	}
	
    }



    

    
    // Write PDV file

    FILE* file = fopen("case.pvd","w");    


    fprintf(file,"<VTKFile type=\"Collection\" version=\"0.1\" byte_order=\"LittleEndian\">\n");
    fprintf(file,"  <Collection>\n");

    uint i;

    for( i = 0 ; i < nt ; i++ ) {

	fprintf(file,"    <DataSet part=\"0\"  timestep=\"%d\" file=\"%d/fields.pvtu\" />\n", tSteps[i], tSteps[i]);

    }
    
    fprintf(file,"  </Collection>\n");
    fprintf(file,"</VTKFile>\n");
    
    

    fclose(file);

}
