#include <openDict.h>

struct dictionary openDict( char* name ) {

    
    // Open file
    
    FILE* fp;

    fp = fopen(name, "r");

    if(fp == NULL) {

    	printf("\n [ERROR]   Unable to open file %s\n\n", name);

    	exit(1);

    }



    // Load dictionary content as single string

    struct dictionary dict;
    
    long length;

    if (fp) {
	
	fseek (fp, 0, SEEK_END);
	
	length = ftell (fp);
	
	fseek (fp, 0, SEEK_SET);

	dict.content = malloc (length);

	if (dict.content)
	{
	    fread (dict.content, 1, length, fp);
	}

	fclose (fp);
    }

    
    /* printf(); */

    return dict;

    

}
