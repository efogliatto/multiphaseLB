#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <D3Q15_MRTInv.h>

scalar** D3Q15_MRTInv() {

    scalar** invM;
    
    invM = (scalar**)malloc( 15 * sizeof(scalar*));

    uint i;

    for( i = 0 ; i < 15 ; i++) {

    	invM[i] = (scalar*)malloc( 15 * sizeof(scalar));
	
    }
    

    invM[0][0]  = 1.0 / 15.0;
    invM[1][0]  = 1.0 / 15.0;
    invM[2][0]  = 1.0 / 15.0;
    invM[3][0]  = 1.0 / 15.0;
    invM[4][0]  = 1.0 / 15.0;
    invM[5][0]  = 1.0 / 15.0;
    invM[6][0]  = 1.0 / 15.0;
    invM[7][0]  = 1.0 / 15.0;
    invM[8][0]  = 1.0 / 15.0;
    invM[9][0]  = 1.0 / 15.0;
    invM[10][0] = 1.0 / 15.0;
    invM[11][0] = 1.0 / 15.0;
    invM[12][0] = 1.0 / 15.0;
    invM[13][0] = 1.0 / 15.0;
    invM[14][0] = 1.0 / 15.0;

    invM[0][1]  = -1.0 / 9.0;
    invM[1][1]  = -1.0 / 18.0;
    invM[2][1]  = -1.0 / 18.0;
    invM[3][1]  = -1.0 / 18.0;
    invM[4][1]  = -1.0 / 18.0;
    invM[5][1]  = -1.0 / 18.0;
    invM[6][1]  = -1.0 / 18.0;
    invM[7][1]  = 1.0 / 18.0;
    invM[8][1]  = 1.0 / 18.0;
    invM[9][1]  = 1.0 / 18.0;
    invM[10][1] = 1.0 / 18.0;
    invM[11][1] = 1.0 / 18.0;
    invM[12][1] = 1.0 / 18.0;
    invM[13][1] = 1.0 / 18.0;
    invM[14][1] = 1.0 / 18.0;

    invM[0][2]  =  2.0 / 45;
    invM[1][2]  = -1.0 / 90.0;
    invM[2][2]  = -1.0 / 90.0;
    invM[3][2]  = -1.0 / 90.0;
    invM[4][2]  = -1.0 / 90.0;
    invM[5][2]  = -1.0 / 90.0;
    invM[6][2]  = -1.0 / 90.0;
    invM[7][2]  =  1.0 / 360.0;
    invM[8][2]  =  1.0 / 360.0;
    invM[9][2]  =  1.0 / 360.0;
    invM[10][2] =  1.0 / 360.0;
    invM[11][2] =  1.0 / 360.0;
    invM[12][2] =  1.0 / 360.0;
    invM[13][2] =  1.0 / 360.0;
    invM[14][2] =  1.0 / 360.0;

    invM[0][3]  =  0;
    invM[1][3]  =  0.1;
    invM[2][3]  = -0.1;
    invM[3][3]  =  0;
    invM[4][3]  =  0;
    invM[5][3]  =  0;
    invM[6][3]  =  0;
    invM[7][3]  =  0.1;
    invM[8][3]  = -0.1;
    invM[9][3]  =  0.1;
    invM[10][3] = -0.1;
    invM[11][3] =  0.1;
    invM[12][3] = -0.1;
    invM[13][3] =  0.1;
    invM[14][3] = -0.1;

    invM[0][4]  =  0;
    invM[1][4]  = -0.1;
    invM[2][4]  =  0.1;
    invM[3][4]  =  0;
    invM[4][4]  =  0;
    invM[5][4]  =  0;
    invM[6][4]  =  0;
    invM[7][4]  =  0.025;
    invM[8][4]  = -0.025;
    invM[9][4]  =  0.025;
    invM[10][4] = -0.025;
    invM[11][4] =  0.025;
    invM[12][4] = -0.025;
    invM[13][4] =  0.025;
    invM[14][4] = -0.025;

    invM[0][5]  =  0;
    invM[1][5]  =  0;
    invM[2][5]  =  0;
    invM[3][5]  =  0.1;
    invM[4][5]  = -0.1;
    invM[5][5]  =  0;
    invM[6][5]  =  0;
    invM[7][5]  =  0.1;
    invM[8][5]  =  0.1;
    invM[9][5]  = -0.1;
    invM[10][5] = -0.1;
    invM[11][5] =  0.1;
    invM[12][5] =  0.1;
    invM[13][5] = -0.1;
    invM[14][5] = -0.1;

    invM[0][6]  =  0;
    invM[1][6]  =  0;
    invM[2][6]  =  0;
    invM[3][6]  = -0.1;
    invM[4][6]  =  0.1;
    invM[5][6]  =  0;
    invM[6][6]  =  0;
    invM[7][6]  =  0.025;
    invM[8][6]  =  0.025;
    invM[9][6]  = -0.025;
    invM[10][6] = -0.025;
    invM[11][6] =  0.025;
    invM[12][6] =  0.025;
    invM[13][6] = -0.025;
    invM[14][6] = -0.025;

    invM[0][7]  =  0;
    invM[1][7]  =  0;
    invM[2][7]  =  0;
    invM[3][7]  =  0;
    invM[4][7]  =  0;
    invM[5][7]  =  0.1;
    invM[6][7]  = -0.1;
    invM[7][7]  =  0.1;
    invM[8][7]  =  0.1;
    invM[9][7]  =  0.1;
    invM[10][7] =  0.1;
    invM[11][7] = -0.1;
    invM[12][7] = -0.1;
    invM[13][7] = -0.1;
    invM[14][7] = -0.1;

    invM[0][8]  =  0;
    invM[1][8]  =  0;
    invM[2][8]  =  0;
    invM[3][8]  =  0;
    invM[4][8]  =  0;
    invM[5][8]  = -0.1;
    invM[6][8]  =  0.1;
    invM[7][8]  =  0.025;
    invM[8][8]  =  0.025;
    invM[9][8]  =  0.025;
    invM[10][8] =  0.025;
    invM[11][8] = -0.025;
    invM[12][8] = -0.025;
    invM[13][8] = -0.025;
    invM[14][8] = -0.025;

    invM[0][9]  =  0;
    invM[1][9]  =  1.0 / 6.0;
    invM[2][9]  =  1.0 / 6.0;
    invM[3][9]  = -1.0 / 12.0;
    invM[4][9]  = -1.0 / 12.0;
    invM[5][9]  = -1.0 / 12.0;
    invM[6][9]  = -1.0 / 12.0;
    invM[7][9]  =  0;
    invM[8][9]  =  0;
    invM[9][9]  =  0;
    invM[10][9] =  0;
    invM[11][9] =  0;
    invM[12][9] =  0;
    invM[13][9] =  0;
    invM[14][9] =  0;

    invM[0][10]  =  0;
    invM[1][10]  =  0;
    invM[2][10]  =  0;
    invM[3][10]  =  0.25;
    invM[4][10]  =  0.25;
    invM[5][10]  = -0.25;
    invM[6][10]  = -0.25;
    invM[7][10]  =  0;
    invM[8][10]  =  0;
    invM[9][10]  =  0;
    invM[10][10] =  0;
    invM[11][10] =  0;
    invM[12][10] =  0;
    invM[13][10] =  0;
    invM[14][10] =  0;

    invM[0][11]  =  0;
    invM[1][11]  =  0;
    invM[2][11]  =  0;
    invM[3][11]  =  0;
    invM[4][11]  =  0;
    invM[5][11]  =  0;
    invM[6][11]  =  0;
    invM[7][11]  =  0.125;
    invM[8][11]  = -0.125;
    invM[9][11]  = -0.125;
    invM[10][11] =  0.125;
    invM[11][11] =  0.125;
    invM[12][11] = -0.125;
    invM[13][11] = -0.125;
    invM[14][11] =  0.125;

    invM[0][12]  =  0;
    invM[1][12]  =  0;
    invM[2][12]  =  0;
    invM[3][12]  =  0;
    invM[4][12]  =  0;
    invM[5][12]  =  0;
    invM[6][12]  =  0;
    invM[7][12]  =  0.125;
    invM[8][12]  =  0.125;
    invM[9][12]  = -0.125;
    invM[10][12] = -0.125;
    invM[11][12] = -0.125;
    invM[12][12] = -0.125;
    invM[13][12] =  0.125;
    invM[14][12] =  0.125;

    invM[0][13]  =  0;
    invM[1][13]  =  0;
    invM[2][13]  =  0;
    invM[3][13]  =  0;
    invM[4][13]  =  0;
    invM[5][13]  =  0;
    invM[6][13]  =  0;
    invM[7][13]  =  0.125;
    invM[8][13]  = -0.125;
    invM[9][13]  =  0.125;
    invM[10][13] = -0.125;
    invM[11][13] = -0.125;
    invM[12][13] =  0.125;
    invM[13][13] = -0.125;
    invM[14][13] =  0.125;

    invM[0][14]  =  0;
    invM[1][14]  =  0;
    invM[2][14]  =  0;
    invM[3][14]  =  0;
    invM[4][14]  =  0;
    invM[5][14]  =  0;
    invM[6][14]  =  0;
    invM[7][14]  =  0.125;
    invM[8][14]  = -0.125;
    invM[9][14]  = -0.125;
    invM[10][14] =  0.125;
    invM[11][14] = -0.125;
    invM[12][14] =  0.125;
    invM[13][14] =  0.125;
    invM[14][14] = -0.125;


    

    return invM;

}
