#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <D3Q15_omega.h>

scalar* D3Q15_omega() {

    scalar* omega;
    
    omega = (scalar*)malloc( 15 * sizeof(scalar));

    omega[0] = 2.0 / 9.0;


    uint i;

    for( i = 1 ; i <= 6 ; i++) {

	omega[i] = 1.0 / 9.0;

    }


    for( i = 7 ; i < 15 ; i++) {

	omega[i] = 1.0 / 72.0;

    }
    

    return omega;

}
