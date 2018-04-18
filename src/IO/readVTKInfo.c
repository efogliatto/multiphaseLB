#include <dictIO.h>
#include <io.h>
#include <vtkInfo.h>

vtkInfo readVTKInfo() {


    vtkInfo vtk;

    unsigned int status;


    
    status = lookUpEntry( "start/initialFields", "scalarFields", vtk.scalarFields, &vtk.nscalar);

    if( !status ) { vtk.nscalar = 0; }

    
    status = lookUpEntry( "start/initialFields", "vectorFields", vtk.vectorFields, &vtk.nvector);

    if( !status ) { vtk.nvector = 0; }
    

    status = lookUpEntry( "start/initialFields", "pdfFields", vtk.pdfFields, &vtk.npdf);

    if( !status ) { vtk.npdf = 0; }


    
    return vtk;

}
