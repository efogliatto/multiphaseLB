#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <D2Q9_ppw.h>

scalar* D2Q9_ppw() {

    scalar* w;
    
    w = (scalar*)malloc( 9 * sizeof(scalar));

    w[0] = 0;
    w[1] = 1.0/3;
    w[2] = 1.0/3;
    w[3] = 1.0/3;
    w[4] = 1.0/3;
    w[5] = 1.0/12;
    w[6] = 1.0/12;
    w[7] = 1.0/12;
    w[8] = 1.0/12;


    return w;

}
