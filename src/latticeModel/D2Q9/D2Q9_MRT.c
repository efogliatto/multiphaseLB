#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dataTypes.h>


scalar** D2Q9_MRT() {

    scalar** M;
    
    M = (scalar**)malloc( 9 * sizeof(scalar*));

    uint i;
    for( i = 0 ; i < 9 ; i++) {

    	M[i] = (scalar*)malloc( 9 * sizeof(scalar));
	
    }

    M[0][0] = 1;
    M[0][1] = 1;
    M[0][2] = 1;
    M[0][3] = 1;
    M[0][4] = 1;
    M[0][5] = 1;
    M[0][6] = 1;
    M[0][7] = 1;
    M[0][8] = 1;
	
    M[1][0] = -4;
    M[1][1] = -1;
    M[1][2] = -1;
    M[1][3] = -1;
    M[1][4] = -1;
    M[1][5] = 2;
    M[1][6] = 2;
    M[1][7] = 2;
    M[1][8] = 2;
	
    M[2][0] =  4;
    M[2][1] = -2;
    M[2][2] = -2;
    M[2][3] = -2;
    M[2][4] = -2;
    M[2][5] =  1;
    M[2][6] =  1;
    M[2][7] =  1;
    M[2][8] =  1;
	
    M[3][0] =  0;
    M[3][1] =  1;
    M[3][2] =  0;
    M[3][3] =  -1;
    M[3][4] =  0;
    M[3][5] =  1;
    M[3][6] =  -1;
    M[3][7] =  -1;
    M[3][8] =  1;
	
    M[4][0] = 0;
    M[4][1] = -2;
    M[4][2] = 0;
    M[4][3] = 2;
    M[4][4] = 0;
    M[4][5] = 1;
    M[4][6] = -1;
    M[4][7] = -1;
    M[4][8] = 1;
	
    M[5][0] = 0;
    M[5][1] = 0;
    M[5][2] = 1;
    M[5][3] = 0;
    M[5][4] = -1;
    M[5][5] = 1;
    M[5][6] = 1;
    M[5][7] = -1;
    M[5][8] = -1;
	
    M[6][0] = 0;
    M[6][1] = 0;
    M[6][2] = -2;
    M[6][3] = 0;
    M[6][4] = 2;
    M[6][5] = 1;
    M[6][6] = 1;
    M[6][7] = -1;
    M[6][8] = -1;
	
    M[7][0] = 0;
    M[7][1] = 1;
    M[7][2] = -1;
    M[7][3] = 1;
    M[7][4] = -1;
    M[7][5] = 0;
    M[7][6] = 0;
    M[7][7] = 0;
    M[7][8] = 0;
	
    M[8][0] = 0;
    M[8][1] = 0;
    M[8][2] = 0;
    M[8][3] = 0;
    M[8][4] = 0;
    M[8][5] = 1;
    M[8][6] = -1;
    M[8][7] = 1;
    M[8][8] = -1;
    


    return M;

}
