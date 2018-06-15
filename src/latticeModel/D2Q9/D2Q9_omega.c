#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <D2Q9_omega.h>

scalar* D2Q9_omega() {

    scalar* omega;
    
    omega = (scalar*)malloc( 9 * sizeof(scalar));

    omega[0] = 4.0 / 9.0;
    omega[1] = 1.0 / 9.0;
    omega[2] = 1.0 / 9.0;
    omega[3] = 1.0 / 9.0;
    omega[4] = 1.0 / 9.0;
    omega[5] = 1.0 / 36.0;
    omega[6] = 1.0 / 36.0;
    omega[7] = 1.0 / 36.0;
    omega[8] = 1.0 / 36.0;


    return omega;

}
