import salome

import sys

import numpy

from salome.geom import geomtools



def latticeMeshPoints(geompy, Cavity):
    '''
    This function returns lattice points inside the geometry
    '''
    bbox = geompy.BoundingBox( Cavity )

    lx = int(  bbox[1] - bbox[0]  )
    ly = int(  bbox[3] - bbox[2]  )

    pointList = []


    for j in range( ly+1 ):

        for i in range( lx+1 ):  

            x = int( bbox[0] ) + i
            y = int( bbox[2] ) + j

            point = geompy.MakeVertex(x, y, 0)

            
            if numpy.isclose( geompy.MinDistance(point, Cavity), 0.0, rtol=1e-05, atol=1e-08, equal_nan=False)==True:
                pointList.append(point)


        
    return pointList







def latticeNeighbours(geompy, shape, points, model):
    '''
    This function returns neighbour indices
    '''

    nb = []

    bbox = geompy.BoundingBox( shape )
    
    if model is "D2Q9":


        # Resize neighbour

        nb = [[-1 for x in range(9)] for y in range( len(points) )] 
            
        
        # Lattice velocities and reverse indices
        xvel = [0, 1, 0, -1, 0, 1, -1, -1, 1]
        yvel = [0, 0, 1, 0, -1, 1, 1, -1, -1]
        zvel = [0, 0, 0, 0, 0, 0, 0, 0, 0]
        rev =  [0, 3, 4, 1, 2, 7, 8, 5, 6]

        nx = int(  bbox[1] - bbox[0]  ) + 1
        ny = int(  bbox[3] - bbox[2]  ) + 1
        nz = int(  bbox[5] - bbox[4]  ) + 1
        

        # Move over points

        for id in range( len(points) ):
            
            for k in range( len(xvel) ):
                
                
                newId = id + xvel[ rev[k] ] + yvel[ rev[k] ]*nx + zvel[ rev[k] ]*nx*ny

                # sys.stdout.write( "%d  " % id  )
                # sys.stdout.write( "%d  " % k  )
                # sys.stdout.write( "%d\n" % newId  )
                
                # Iterate in backward direction (minimices the number of searches)
                
                if newId >= id:

                    
                    if newId >= len(points):
                            
                        newId = len(points)-1

                            
                    find = False;

                    
                    while (newId >= id)  and  (find is False) :

                        newCoord = geompy.PointCoordinates( points[newId] )

                        coord = geompy.PointCoordinates( points[id] )


                        # Point differences
                        
                        xdiff = newCoord[0] - coord[0] - xvel[ rev[k] ]
                        ydiff = newCoord[1] - coord[1] - yvel[ rev[k] ]
                        zdiff = newCoord[2] - coord[2] - zvel[ rev[k] ]

                        if numpy.isclose( xdiff*xdiff + ydiff*ydiff + zdiff*zdiff, 0.0, rtol=1e-05, atol=1e-08, equal_nan=False)==True:

                            find = True;

                            nb[id][k] = newId                             


                            
                        newId = newId - 1;
                            



                # Iterate in forward direction

                else:

                    
                    if newId < 0:

                        newId = 0

                        
                    find = False
                        

                    while (newId <= id)  and  (find is False) :


                        newCoord = geompy.PointCoordinates( points[newId] )

                        coord = geompy.PointCoordinates( points[id] )


                        # Point differences
                        
                        xdiff = newCoord[0] - coord[0] - xvel[ rev[k] ]
                        ydiff = newCoord[1] - coord[1] - yvel[ rev[k] ]
                        zdiff = newCoord[2] - coord[2] - zvel[ rev[k] ]

                        
                        if numpy.isclose( xdiff*xdiff + ydiff*ydiff + zdiff*zdiff, 0.0, rtol=1e-05, atol=1e-08, equal_nan=False)==True:

                            find = True;

                            nb[id][k] = newId 
                            

                        
                        newId = newId + 1
        
        
    return nb



def latticeBoundaries(geompy, shape, ftList, points, nb):


    # Initialize boundary doctionary
    
    bdDict = {}

    for ft in ftList:

        bdDict[ ft.GetName() ] = []
        
    count = 0

    
    # Move over points. If some neighbour is -1, look for closest edge/face

    for id in range( len(points) ):

        
        bd = False

        
        for k in range( len(nb[id]) ):

            if nb[id][k] is -1:

                bd = True



       # Look for closest boundary

        if bd is True:

            
            dist = 1000

            ft_id = 0
        
        
            for ft in range( len(ftList) ):

                distAux = geompy.MinDistance( ftList[ft], points[id] )

                if distAux < dist:

                    dist = distAux

                    ft_id = ft



            # Add point index to boundary dictionary

            bdDict[ ftList[ft_id].GetName() ].append(id)



            

    return bdDict







def vtkCells(geompy, nb):

    vtk = []

    rev =  [0, 3, 4, 1, 2, 7, 8, 5, 6]

    
    for id in range( len(nb) ):

        cell = []
        
        cell.append( id )

        
        for k in [3,7,4]:

            aux = nb[id][k]
            
            if aux != -1:

                cell.append(aux)


                
        if len(cell) is 4:

            a = cell[3]

            cell[3] = cell[2]

            cell[2] = a

            vtk.append( cell )


            
    return vtk
