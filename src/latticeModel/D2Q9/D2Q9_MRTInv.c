#include <stdio.h>
#include <string.h>
#include <stdlib.h>


double** D2Q9_MRTInv() {

    double** invM;
    
    invM = (double**)malloc( 9 * sizeof(double*));

    uint i;
    for( i = 0 ; i < 9 ; i++) {

    	invM[i] = (double*)malloc( 9 * sizeof(double));
	
    }


    double c1 = 1.0 / 9.0,
	   c2 = 1.0 / 6.0,
	   c3 = 1.0 / 4.0;    
    



    invM[0][0] =  c1;
    invM[0][1] = -c1;
    invM[0][2] =  c1;
    invM[0][3] =   0;
    invM[0][4] =       0;
    invM[0][5] =     0;
    invM[0][6] =       0;
    invM[0][7] =   0;
    invM[0][8] =    0;
    
    invM[1][0] = c1;
    invM[1][1] =   -c1/4;
    invM[1][2] =   -c1/2;
    invM[1][3] =    c2;
    invM[1][4] =     -c2;
    invM[1][5] =     0;
    invM[1][6] =       0;
    invM[1][7] =  c3;
    invM[1][8] =    0;
    
    invM[2][0] = c1;
    invM[2][1] =   -c1/4;
    invM[2][2] =   -c1/2;
    invM[2][3] =     0;
    invM[2][4] =       0;
    invM[2][5] =    c2;
    invM[2][6] =     -c2;
    invM[2][7] = -c3;
    invM[2][8] =    0;
    
    invM[3][0] = c1;
    invM[3][1] =   -c1/4;
    invM[3][2] =   -c1/2;
    invM[3][3] =   -c2;
    invM[3][4] =      c2;
    invM[3][5] =     0;
    invM[3][6] =       0;
    invM[3][7] =  c3;
    invM[3][8] =    0;
    
    invM[4][0] = c1;
    invM[4][1] =   -c1/4;
    invM[4][2] =   -c1/2;
    invM[4][3] =     0;
    invM[4][4] =       0;
    invM[4][5] =   -c2;
    invM[4][6] =      c2;
    invM[4][7] = -c3;
    invM[4][8] =    0;
    
    invM[5][0] = c1;
    invM[5][1] =    c1/2;
    invM[5][2] =    c1/4;
    invM[5][3] =    c2;
    invM[5][4] =    c2/2;
    invM[5][5] =    c2;
    invM[5][6] =    c2/2;
    invM[5][7] =   0;
    invM[5][8] =   c3;
    
    invM[6][0] = c1;
    invM[6][1] =    c1/2;
    invM[6][2] =    c1/4;
    invM[6][3] =   -c2;
    invM[6][4] =   -c2/2;
    invM[6][5] =    c2;
    invM[6][6] =    c2/2;
    invM[6][7] =   0;
    invM[6][8] =  -c3;
    
    invM[7][0] = c1;
    invM[7][1] =    c1/2;
    invM[7][2] =    c1/4;
    invM[7][3] =   -c2;
    invM[7][4] =   -c2/2;
    invM[7][5] =   -c2;
    invM[7][6] =   -c2/2;
    invM[7][7] =   0;
    invM[7][8] =   c3;
    
    invM[8][0] = c1;
    invM[8][1] =    c1/2;
    invM[8][2] =    c1/4;
    invM[8][3] =    c2;
    invM[8][4] =    c2/2;
    invM[8][5] =   -c2;
    invM[8][6] =   -c2/2;
    invM[8][7] =   0;
    invM[8][8] =  -c3;

    

    return invM;

}
