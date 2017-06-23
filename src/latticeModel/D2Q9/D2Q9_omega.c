#include <stdio.h>
#include <string.h>
#include <stdlib.h>


double* D2Q9_omega() {

    double* omega;
    
    omega = (double*)malloc( 9 * sizeof(double));

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
