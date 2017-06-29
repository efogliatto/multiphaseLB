#ifndef VTKINFO_H
#define VTKINFO_H

struct vtkInfo {

    // Total number of scalar fields
    unsigned int nscalar;

    // Total number of vector fields
    unsigned int nvector;

    // Total number of pdf fields
    unsigned int npdf;

    // Scalar fields
    char scalarFields[10][100];

    // Vector fields
    char vectorFields[10][100];

    // Pdf fields
    char pdfFields[10][100];
    
};

#endif // VTKINFO_H
