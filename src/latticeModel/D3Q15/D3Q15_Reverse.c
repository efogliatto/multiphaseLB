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
    vel[7] = 14;
    vel[8] = 13;
    vel[9] = 12;
    vel[10] = 11;
    vel[11] = 10;
    vel[12] = 9;
    vel[13] = 8;
    vel[14] = 7;
    
    return vel;

}
