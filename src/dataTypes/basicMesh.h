#ifndef BASICMESH_H
#define BASICMESH_H


struct basicBoundary {

    // Number of boundary types
    unsigned int nbd;

    // Total number of elements per boundary type
    unsigned int* nbdelem;

    // Boundary names (max 100 boundaries)
    char bdNames[100][100];

    // Elements in boundary
    unsigned int** bdPoints;    

};


struct basicMesh {

    
    // Points
    unsigned int nPoints;
    int** points;

    // Neighbours
    unsigned int Q;
    char lbm[100];
    int** nb;

    // Boundary
    struct basicBoundary bd;

    // VTK Cells
    unsigned int ncells;
    unsigned int cellType;
    int** vtkCells;

};





#endif // BASICMESH_H
