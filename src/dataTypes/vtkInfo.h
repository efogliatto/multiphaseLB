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
    char** scalarFields;

    // Vector fields
    char** vectorFields;

    // Pdf fields
    char** pdfFields;    
    
};

#endif // VTKINFO_H
