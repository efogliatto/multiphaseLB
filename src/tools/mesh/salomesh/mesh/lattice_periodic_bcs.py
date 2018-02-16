import salome

import sys

import numpy as np

from salome.geom import geomtools


def lattice_periodic_bcs(geompy, nb, bdDict, periodicBCs):


    newNb = np.copy(nb)
    

    # Move over periodic boundaries and reassign neighbours

    for bdPair in periodicBCs:

        
        for i in range(  len( bdDict[ bdPair[0] ] )  ):

            id = bdDict[ bdPair[0] ][i]

            nid = bdDict[ bdPair[1] ][i]
                

            for k in range(9):

                
                if newNb[id][k] == -1:

                    newNb[id][k] = newNb[nid][k]

                    
                if newNb[nid][k] == -1:

                    newNb[nid][k] = newNb[id][k]



    return newNb
