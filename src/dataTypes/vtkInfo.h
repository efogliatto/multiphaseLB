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
    char scalarFields[10][100];   

    /** Vector fields names*/
    char vectorFields[10][100];   

    /** Pdf fields names*/
    char pdfFields[10][100];   
    
} vtkInfo;

#endif // VTKINFO_H
