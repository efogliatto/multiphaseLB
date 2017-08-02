# -*- coding: utf-8 -*-

###
### This file is generated automatically by SALOME v8.2.0 with dump python functionality
###

import sys
import salome

salome.salome_init()
theStudy = salome.myStudy

import salome_notebook
notebook = salome_notebook.NoteBook(theStudy)


# import own functions
from latticeMesh import *
from writeMesh import *


###
### GEOM component
###

import GEOM
from salome.geom import geomBuilder
import math
import SALOMEDS
import numpy


Xc = 5
Yc = 5


geompy = geomBuilder.New(theStudy)

O = geompy.MakeVertex(0, 0, 0)
OX = geompy.MakeVectorDXDYDZ(1, 0, 0)
OY = geompy.MakeVectorDXDYDZ(0, 1, 0)
OZ = geompy.MakeVectorDXDYDZ(0, 0, 1)

geompy.addToStudy( O, 'O' )
geompy.addToStudy( OX, 'OX' )
geompy.addToStudy( OY, 'OY' )
geompy.addToStudy( OZ, 'OZ' )


# Cavity vertices
Vertex_1 = geompy.MakeVertex(0, 0, 0)
Vertex_2 = geompy.MakeVertex(Xc, 0, 0)
Vertex_3 = geompy.MakeVertex(Xc, Yc, 0)
Vertex_4 = geompy.MakeVertex(0, Yc, 0)


Line_11 = geompy.MakeLineTwoPnt(Vertex_1, Vertex_2)
Line_21 = geompy.MakeLineTwoPnt(Vertex_2, Vertex_3)
Line_31 = geompy.MakeLineTwoPnt(Vertex_3, Vertex_4)
Line_41 = geompy.MakeLineTwoPnt(Vertex_4, Vertex_1)


# Make face from lines
Wire_2 = geompy.MakeWire([Line_11, Line_21, Line_31, Line_41], 1e-07)

Box = geompy.MakeFaceWires([Wire_2], 1)
geompy.addToStudy( Box, 'Box' )



# List of edges. Assign names according to index

Box_EdgeList = geompy.ExtractShapes(Box, geompy.ShapeType["EDGE"], True)

for i in range( len(Box_EdgeList) ):
  Box_EdgeList[i].SetName("Edge_" + `i`)
  geompy.addToStudyInFather( Box, Box_EdgeList[i], Box_EdgeList[i].GetName() )




# Point creation

points = latticeMeshPoints(geompy, Box)


# Neighbour creation

nb = latticeNeighbours(geompy, Box, points, "D2Q9")


# Boundaries detection

bdDict = latticeBoundaries(geompy, Box, Box_EdgeList, points, nb)


# VTKCells

vtk = vtkCells(geompy, nb)



# Write mesh info in LB format

writePoints( geompy, points )

writeNeighbours( geompy, nb )

writeBoundaries( geompy, bdDict )

writeVTKCells( geompy, vtk )



  
  
  

if salome.sg.hasDesktop():
  salome.sg.updateObjBrowser(True)
