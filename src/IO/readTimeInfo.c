#include <io.h>

void readTimeInfo( struct latticeMesh* mesh ) {

    
    double aux;

    
    // Start time

    aux = lookUpDoubleEntry("properties/simulation","startTime",0);
    
    mesh->time.start = (unsigned int)aux;

    mesh->time.current = mesh->time.start;

    mesh->time.stp = 0;
    


    // End time

    aux = lookUpDoubleEntry("properties/simulation","endTime",0);
    
    mesh->time.end = (unsigned int)aux;


    
    // Write interval

    aux = lookUpDoubleEntry("properties/simulation","writeInterval",1);
    
    mesh->time.writeInterval = (unsigned int)aux;



    // Measure time

    mesh->time.st = time( NULL );

    gettimeofday( &mesh->time.stt, NULL );
    

}
