#include <dictIO.h>
#include <io.h>
#include <latticeMesh.h>
#include <stdlib.h>
#include <stdio.h>
#include <basic.h>
#include <math.h>


/* void sphereBoundedScalarField( latticeMesh* mesh, scalar** field, char* fname ) { */


/*     // Allocate memory */
    
/*     *field = (scalar*)malloc( mesh->mesh.nPoints * sizeof(scalar) ); */


    
/*     // Look for values */

/*     char* aux; */

/*     scalar in = 0, */
/* 	out = 0; */

/*     scalar* centre; */

/*     scalar radius; */

/*     uint status, */
/* 	n; */

    
/*     // Centre */
    
/*     if(  vstring(&aux, "%s/internalField/centre", fname)  ) */
/* 	status = lookUpVectorEntry("start/initialFields", aux, &centre, &n); */

    

/*     // Radius */

/*     char* ins; */
    
/*     if(  vstring(&ins, "%s/internalField/radius", fname)  )     */
/* 	status = lookUpScalarEntry("start/initialFields", ins, 0, &radius); */
    

/*     // Inside value */
    
/*     if(  vstring(&ins, "%s/internalField/inside", fname)  )     */
/* 	status = lookUpScalarEntry("start/initialFields", ins, 0, &in); */



/*     // Outside value */
    
/*     if(  vstring(&ins, "%s/internalField/outside", fname)  )     */
/* 	status = lookUpScalarEntry("start/initialFields", ins, 0, &out); */

    
    
/*     if (status) {} */
    
    
/*     uint ii; */

/*     for( ii = 0 ; ii < mesh->mesh.nPoints ; ii++ ) { */

/* 	scalar r = ( mesh->mesh.points[ii][0] - centre[0] )  *  ( mesh->mesh.points[ii][0] - centre[0] ) + */
/* 	    ( mesh->mesh.points[ii][1] - centre[1] )  *  ( mesh->mesh.points[ii][1] - centre[1] ) +  */
/* 	    ( mesh->mesh.points[ii][2] - centre[2] )  *  ( mesh->mesh.points[ii][2] - centre[2] ); */

/* 	if( r < radius * radius ) { */
	
/* 	    field[0][ii] = in; */

/* 	} */

/* 	else { */

/* 	    /\* if(mesh->mesh.points[ii][1] <= (centre[1] - radius)) { *\/ */
		
/* 	    /\* 	field[0][ii] = in; *\/ */
		
/* 	    /\* } *\/ */

/* 	    /\* else{ *\/ */

/* 		field[0][ii] = out; */

/* 	    /\* } *\/ */

/* 	} */

/*     } */
    

/*     free(aux); */

/*     free(centre); */

/* } */







void sphereBoundedScalarField( latticeMesh* mesh, scalar** field, char* fname ) {


    // Allocate memory
    
    *field = (scalar*)malloc( mesh->mesh.nPoints * sizeof(scalar) );


    
    // Look for values

    char* aux;

    scalar in = 0,
	out = 0;

    scalar* centre;

    scalar R;

    scalar W;

    uint status,
	n;

    
    // Centre
    
    if(  vstring(&aux, "%s/internalField/centre", fname)  )
	status = lookUpVectorEntry("start/initialFields", aux, &centre, &n);

    

    // Radius

    char* ins;
    
    if(  vstring(&ins, "%s/internalField/radius", fname)  )    
	status = lookUpScalarEntry("start/initialFields", ins, 0, &R);


    // Width

    if(  vstring(&ins, "%s/internalField/width", fname)  )    
	status = lookUpScalarEntry("start/initialFields", ins, 0, &W);    
    

    // Inside value
    
    if(  vstring(&ins, "%s/internalField/inside", fname)  )    
	status = lookUpScalarEntry("start/initialFields", ins, 0, &in);



    // Outside value
    
    if(  vstring(&ins, "%s/internalField/outside", fname)  )    
	status = lookUpScalarEntry("start/initialFields", ins, 0, &out);

    
    
    if (status) {}
    
    
    uint ii;

    for( ii = 0 ; ii < mesh->mesh.nPoints ; ii++ ) {

	scalar r = ( mesh->mesh.points[ii][0] - centre[0] )  *  ( mesh->mesh.points[ii][0] - centre[0] ) +
	    ( mesh->mesh.points[ii][1] - centre[1] )  *  ( mesh->mesh.points[ii][1] - centre[1] ) + 
	    ( mesh->mesh.points[ii][2] - centre[2] )  *  ( mesh->mesh.points[ii][2] - centre[2] );

	
	field[0][ii] = 0.5*( in + out )    +   0.5*( out - in ) * tanh( (2*sqrt(r) - R) / W )  ;

    }
    

    free(aux);

    free(centre);

}
