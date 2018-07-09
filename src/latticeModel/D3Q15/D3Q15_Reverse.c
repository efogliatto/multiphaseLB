#include <stdio.h>
#include <stdlib.h>
#include <D3Q15_Reverse.h>

int* D3Q15_Reverse() {

    int* vel;
    
    vel = (int*)malloc( 15 * sizeof(int));

    vel[0] = 0;
    vel[1] = 2;
    vel[2] = 1;
    vel[3] = 4;
    vel[4] = 3;
    vel[5] = 6;
    vel[6] = 5;
    vel[7] = 11;
    vel[8] = 12;
    vel[9] = 13;
    vel[10] = 14;
    vel[11] = 7;
    vel[12] = 8;
    vel[13] = 9;
    vel[14] = 10;
    
    return vel;

}
