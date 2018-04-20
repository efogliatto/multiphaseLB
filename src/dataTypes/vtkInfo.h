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

typedef struct {

    /** Total number of scalar fields */
    unsigned int nscalar;   

    /** Total number of vector fields */
    unsigned int nvector;   

    /** Total number of pdf fields */
    unsigned int npdf;   

    /** Scalar fields names*/
    char** scalarFields;   

    /** Vector fields names*/
    char** vectorFields;

    /** Pdf fields names*/
    char** pdfFields;
    
} vtkInfo;

#endif // VTKINFO_H
