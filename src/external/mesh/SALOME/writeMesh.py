import sys
import os
import salome
import numpy
from salome.geom import geomtools


def writePoints( geompy, points ):

    directory = "lattice"
    
    if not os.path.exists(directory):
        os.makedirs(directory)
    
    file = open(directory + "/points", 'w')


    # Number of points
    
    file.write( str(len(points)) )
    file.write( "\n" )


    for point in points:

        coord = geompy.PointCoordinates(point)

        file.write( "%.0f " % coord[0] )
        file.write( "%.0f " % coord[1] )
        file.write( "%.0f\n" % coord[2] )


    file.close()





def writeNeighbours( geompy, nb ):

    directory = "lattice"
    
    if not os.path.exists(directory):
        os.makedirs(directory)
    
    file = open(directory + "/neighbours", 'w')


    for nbi in nb:

        
        for i in nbi:

            file.write( "%.0f " % i )


            
        file.write( "\n" )


    file.close()





def writeBoundaries( geompy, bd ):

    directory = "lattice"
    
    if not os.path.exists(directory):
        os.makedirs(directory)
    
    file = open(directory + "/boundary", 'w')


    # Number of points
    
    file.write( str(len(bd.keys())) )
    file.write( "\n" )


    for key, value in bd.iteritems() :

        file.write( "\n" )
        file.write( key )
        file.write( "\n" )
        file.write( str(len(value)) )
        file.write( "\n" )


        for id in value:
            file.write("%d\n" % id)
        
    

    file.close()
    



    

    
def writeVTKCells( geompy, cells ):

    directory = "lattice"
    
    if not os.path.exists(directory):
        os.makedirs(directory)
    
    file = open(directory + "/vtkCells", 'w')

    file.write( str( len(cells) )  )
    file.write( " 4\n" )
    

    for cell in cells:
        
        for i in cell:

            file.write( "%.0f " % i )

            
        file.write( "\n" )


    file.close()
