#ifndef VTKINFO_H
#define VTKINFO_H

/**
 * @file vtkInfo.h
 * @author Ezequiel O. Fogliatto
 * @date 15 Dic 2017
 * @brief VTK output information
 */

/**
 * @brief VTK output information
 *
 * Information related to VTK uotput
 */

#include <dataTypes.h>

typedef struct {

    /** Total number of scalar fields */
    uint nscalar;   

    /** Total number of vector fields */
    uint nvector;   

    /** Total number of pdf fields */
    uint npdf;   

    /** Scalar fields names*/
    char** scalarFields;   

    /** Vector fields names*/
    char** vectorFields;

    /** Pdf fields names*/
    char** pdfFields;
    
} vtkInfo;

#endif // VTKINFO_H
