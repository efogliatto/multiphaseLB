#include <basic.h>

int main() {

    char* msg;
    
    unsigned int status = vstring(&msg, "%s/Lambda", "fafafad");

    if(status)
    	printf("%s\n",msg);
    
    
    return 0;

}



    /* // Read model from file */
    /* char c[100]; */
    /* lookUpStringEntry("input","LBModel", c); */
    
    /* printf("\n"); */
    /* printf("LBModel: %s\n",c); */
    /* printf("\n"); */


    

    /* // Lattice velocities */
    /* unsigned int i;     */
    /* int** lvel = latticeVelocities(c); */

    /* printf("\nVelocities\n"); */
    /* for( i = 0 ; i < 9 ; i++) { */

    /* 	printf(" %d  %d  %d\n",lvel[i][0],lvel[i][1],lvel[i][2]); */
	
    /* } */
    /* printf("\n\n"); */




    /* // Lattice weights     */
    /* double* omega = latticeWeights(c); */

    /* printf("\nWeights\n"); */
    /* for( i = 0 ; i < 9 ; i++) { */

    /* 	printf(" %f\n",omega[i]); */
	
    /* } */
    /* printf("\n\n");     */

    

    /* // Reverse directions */
    /* int* rev = latticeReverseDir(c); */

    /* printf("\nReverse dir\n"); */
    /* for( i = 0 ; i < 9 ; i++) { */

    /* 	printf(" %d\n",rev[i]); */
	
    /* } */
    /* printf("\n\n");     */



    /* // MRT Matrix    */
    /* double** M = MRTMatrix(c); */

    /* printf("\nMRT\n"); */
    /* int j; */
    /* for( i = 0 ; i < 9 ; i++) { */

    /* 	for( j = 0 ; j < 9 ; j++) { */

    /* 	    printf("%.0f ",M[i][j]); */

    /* 	} */
	
    /* 	printf("\n"); */
	
    /* } */
    /* printf("\n\n"); */


    

    /* // MRT Inv Matrix    */
    /* double** invM = MRTInvMatrix(c); */

    /* printf("\nMRT Inv\n"); */
    /* for( i = 0 ; i < 9 ; i++) { */

    /* 	for( j = 0 ; j < 9 ; j++) { */

    /* 	    printf("%f ",invM[i][j]); */

    /* 	} */
	
    /* 	printf("\n"); */
	
    /* } */
    /* printf("\n\n");      */
    








    /* // Pseudo pot w */
    /* double* w = ppWeights(c); */

    /* printf("\nPP W\n"); */
    /* for( i = 0 ; i < 9 ; i++) { */

    /* 	printf(" %f\n",w[i]); */
	
    /* } */
    /* printf("\n\n");  */





    /* printf("\ncs2: %f\n\n",cs2(c)); */

