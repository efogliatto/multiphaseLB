#include <latticeModel.h>
#include <io.h>

int main() {


    // Read model from file
    char c[100];
    lookUpStringEntry("input","LBModel", c);
    
    printf("\n");
    printf("LBModel: %s\n",c);
    printf("\n");


    

    // Lattice velocities
    unsigned int i;    
    int** lvel = latticeVelocities(c);

    printf("\nVelocities\n");
    for( i = 0 ; i < 9 ; i++) {

    	printf(" %d  %d  %d\n",lvel[i][0],lvel[i][1],lvel[i][2]);
	
    }
    printf("\n\n");




    // Lattice weights    
    double* omega = latticeWeights(c);

    printf("\nWeights\n");
    for( i = 0 ; i < 9 ; i++) {

    	printf(" %f\n",omega[i]);
	
    }
    printf("\n\n");    

    

    // Reverse directions
    int* rev = latticeReverseDir(c);

    printf("\nReverse dir\n");
    for( i = 0 ; i < 9 ; i++) {

    	printf(" %d\n",rev[i]);
	
    }
    printf("\n\n");    
    
    
    return 0;

}
