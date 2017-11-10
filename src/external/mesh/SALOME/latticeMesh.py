import salome

import sys

import numpy as np

from salome.geom import geomtools



def latticeMeshPoints(geompy, shape):
    
    '''
    This function returns lattice points inside the geometry bounding box
    
    No shape checking!

    '''

    bbox = geompy.BoundingBox( shape )

    nx = int(  bbox[1] - bbox[0]  ) + 1
    ny = int(  bbox[3] - bbox[2]  ) + 1
    

    pointList = np.zeros( (nx*ny, 3) )


    for j in range(ny):

        for i in range(nx):

            pointList[i+j*nx,0] = int( bbox[0] ) + i
            pointList[i+j*nx,1] = int( bbox[2] ) + j


        
    return pointList







def latticeNeighbours(geompy, shape, points, model):
    
    '''
    This function returns neighbour indices
    '''

    nb = []

    bbox = geompy.BoundingBox( shape )
    
    if model is "D2Q9":


        
        # Resize neighbour

        nb = -1. + np.zeros( (len(points),9) )
            

        
        # Lattice velocities and reverse indices
        
        vel = np.array( [[0,0,0], [1,0,0], [0,1,0], [-1,0,0], [0,-1,0], [1,1,0], [-1,1,0], [-1,-1,0], [1,-1,0] ])

        rev =  [0, 3, 4, 1, 2, 7, 8, 5, 6]


        
        # Mesh. number of points
        
        nx = int(  bbox[1] - bbox[0]  ) + 1
        ny = int(  bbox[3] - bbox[2]  ) + 1
        nz = int(  bbox[5] - bbox[4]  ) + 1
        


        # Internal points first

        for j in range(1,ny-1):

            for i in range(1,nx-1):

                pointId = i + j*nx


                # Iterate on velocities

                for velId in range(9):

                    nb[pointId,velId] = pointId   +   vel[ rev[velId], 0]   +   vel[ rev[velId] , 1] * nx



                    
    # For boundary nodes, check neighbouring using distance to point

    for j in range(0,ny,ny-1):

        for i in range(nx):

            pointId = i+j*nx


    	    # Iterate on velocities

            for velId in range(9):
                
    		newId = pointId   +   vel[ rev[velId] ,0]   +   vel[ rev[velId] ,1] * nx
                

    		if  newId >= 0  and   newId <= nx*ny-1:

    		    if ( (  np.abs( points[pointId,0] - points[newId,0] ) <= 1  )   and   (  np.abs( points[pointId,1] - points[newId,1] ) <= 1  )  ):
	    
    			nb[pointId,velId] = newId



    for j in range(1,ny-1):

        for i in range(0,nx,nx-1):

    	    pointId = i + j*nx

            
     	    # Iterate on velocities
            
            for velId in range(9):

    		newId = pointId   +   vel[ rev[velId] ,0]   +   vel[ rev[velId] ,1] * nx
                

    		if  newId >= 0  and   newId <= nx*ny-1:

    		    if ( (  np.abs( points[pointId,0] - points[newId,0] ) <= 1  )   and   (  np.abs( points[pointId,1] - points[newId,1] ) <= 1  )  ):
	    
    			nb[pointId,velId] = newId
	        
        
        
    return nb




def pointsInShape(geompy, shape, points):

    """
    Check which points are inside shape, and change index
    """

    newPid = -1 + np.zeros( len(points), dtype = int )

    newPoints = []

    id = 0


    for i in range( len(points) ):

        pt = geompy.MakeVertex(points[i,0], points[i,1], points[i,2])

        if np.isclose( geompy.MinDistance(shape, pt), 0 ) == True:

            newPid[i] = id
            
            id = id + 1

            newPoints.append(pt)
    
    

    return newPid, newPoints







def removeNeighbours(geompy, pindex, nb, n ):

    """
    New neighbour array. Remove non existing neighbours based on indices
    """

    newNeigh = -1 + np.zeros( (n, nb.shape[1]), dtype = int )

    Q = nb.shape[1]


   
    for i, id in enumerate(pindex):
        
        if id != -1:

            for vid in range(Q):

                if nb[i][vid] != -1:

                    newNeigh[id][vid] = pindex[ nb[i][vid] ]
    
    
    return newNeigh






def mesh(geompy, shape, model):

    """
    Lattice mesh creation
    """


    # Point creation

    base_points = latticeMeshPoints(geompy, shape)


    
    # Neighbour creation

    base_nb = latticeNeighbours(geompy, shape, base_points, model)


    
    # Points inside geometry

    npid,points = pointsInShape(geompy, shape, base_points)


    
    # Non existing neighbours removal

    nb = removeNeighbours(geompy, npid, base_nb, len(points) )


    

    return points, nb


    

def latticeBoundaries(geompy, shape, ftList, points, nb):


    # Initialize boundary dictionary
    
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










def latticeBoundariesWeights(geompy, shape, ftList, points, nb, bdWeights):

    

    # Initialize boundary dictionary
    
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



       # Look for closest boundary.
       # Preference for periodic boundaries

        if bd is True:

            
            dist = []
            
        
            for ft in ftList:

                distAux = geompy.MinDistance( ft, points[id] )

                dist.append( (ft.GetName(), distAux) )


                
            # Sort according to distance

            sortedDist = sorted( dist, key=lambda ftDist: ftDist[1] )



            
            # First check if two features have same distance. Then assign priority for boundary elements

            if numpy.isclose( sortedDist[0][1], sortedDist[1][1], rtol=1e-05, atol=1e-08, equal_nan=False) == True:

                if bdWeights[ sortedDist[0][0] ] < bdWeights[ sortedDist[1][0] ]:
                    
                    c = sortedDist[0]

                    sortedDist[0] = sortedDist[1]

                    sortedDist[1] = c




            bdDict[ sortedDist[0][0] ].append(id)





            

    return bdDict







def latticePeriodicBCs(geompy, nb, bdDict, periodicBCs):


    newNb = nb
    
    # Move over periodic boundaries and reassign neighbours

    for bdPair in periodicBCs:

        for i in range(  len( bdDict[ bdPair[0] ] )  ):

            id = bdDict[ bdPair[0] ][i]

            nid = bdDict[ bdPair[1] ][i]
                

            for k in range(9):

                
                if newNb[id][k] is -1:

                    newNb[id][k] = newNb[nid][k]

                    
                if newNb[nid][k] is -1:

                    newNb[nid][k] = newNb[id][k]



    return newNb




    


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
