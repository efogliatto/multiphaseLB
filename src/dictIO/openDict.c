#include <openDict.h>
#include <basic.h>

dictionary openDict( char* name ) {

    
    // Open file
    
    FILE* fp;

    fp = fopen(name, "r");

    testFile(fp, name);
    
    /* if(fp == NULL) { */

    /* 	printf("\n [ERROR]   Unable to open file %s\n\n", name); */

    /* 	exit(1); */

    /* } */



    // Load dictionary content as single string

    dictionary dict;
    
    int length = 0;

    char word[100];

    while( fscanf(fp,"%s",word) != EOF ) {

      length = length + strlen(word) + 1;

    }

    /* length; */



    // Allocate space for dictionary content

    dict.content = malloc(length);

    memset(dict.content,' ',length);



    fseek (fp, 0, SEEK_SET);

    unsigned int pos = 0,
      i;

    if (dict.content) {

      while( fscanf(fp,"%s",word) != EOF ) {

    	for( i = 0 ; i < strlen(word) ; i++ ) {

    	  dict.content[i+pos] = word[i];

    	}

    	pos = pos + strlen(word) + 1;

      }


    }



    dict.version = 1;

    fclose(fp);


    return dict;

    

}
