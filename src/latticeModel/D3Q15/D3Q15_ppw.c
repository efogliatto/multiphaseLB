#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <D3Q15_ppw.h>

scalar* D3Q15_ppw() {

    scalar* w;
    
    w = (scalar*)malloc( 15 * sizeof(scalar));

    w[0] = 0;

    uint i;


    for( i = 1 ; i <= 6 ; i++ ) {

	w[i] = 1.0 / 3.0;

    }


    for( i = 7 ; i < 15 ; i++ ) {

	w[i] = 1.0 / 24.0;

    }    
    

    return w;

}
