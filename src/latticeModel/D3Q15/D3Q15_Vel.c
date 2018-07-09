#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <D3Q15_Vel.h>


int** D3Q15_Vel() {

    int** vel;
    
    vel = (int**)malloc( 15 * sizeof(int*));

    uint i;
    for( i = 0 ; i < 15 ; i++) {

    	vel[i] = (int*)malloc( 3 * sizeof(int));
	
    }

    vel[0][0] = 0;
    vel[0][1] = 0;
    vel[0][2] = 0;
    
    vel[1][0] = 1;
    vel[1][1] = 0;
    vel[1][2] = 0;

    vel[2][0] = -1;
    vel[2][1] = 0;
    vel[2][2] = 0;

    vel[3][0] = 0;
    vel[3][1] = 1;
    vel[3][2] = 0;

    vel[4][0] = 0;
    vel[4][1] = -1;
    vel[4][2] = 0;

    vel[5][0] = 0;
    vel[5][1] = 0;
    vel[5][2] = 1;

    vel[6][0] = 0;
    vel[6][1] = 0;
    vel[6][2] = -1;

    vel[7][0] = 1;
    vel[7][1] = 1;
    vel[7][2] = 1;

    vel[8][0] = -1;
    vel[8][1] = 1;
    vel[8][2] = 1;
    
    vel[9][0] = 1;
    vel[9][1] = -1;
    vel[9][2] = 1;
    
    vel[10][0] = -1;
    vel[10][1] = -1;
    vel[10][2] = 1;

    vel[11][0] = 1;
    vel[11][1] = 1;
    vel[11][2] = -1;

    vel[12][0] = -1;
    vel[12][1] = 1;
    vel[12][2] = -1;

    vel[13][0] = 1;
    vel[13][1] = -1;
    vel[13][2] = -1;

    vel[14][0] = -1;
    vel[14][1] = -1;
    vel[14][2] = -1;

    
    return vel;

}
