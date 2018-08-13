#ifndef MPIINFO_H
#define MPIINFO_H

/**< MPI buffer size */
#define MPI_BUFF_SIZE 500  

/**
 * @file mpiInfo.h
 * @author Ezequiel O. Fogliatto
 * @date 15 Dic 2017
 * @brief Struct containing mpi information
 */

/**
 * @brief Struct containing mpi information
 *
 * This struct contains information related to mpi communications
 */

#include <dataTypes.h>

typedef struct {

    
    /**< Process id */
    
    uint pid;   


    /**< Total number of processes */
    
    uint worldSize;   


    /**< Total number of ghosts */
    
    uint nghosts;   


    /**< Number of local elements */
    
    uint nlocal;   


    /**< Receive ghosts indices*/
    
    uint** recvGhosts;   


    /**< Send ghosts indices*/
    
    uint** sendGhosts;           


    /**< Number of receive ghosts */
    
    uint* nrg;   


    /**< Number of send ghosts */
    
    uint* nsg;


    /** Total number of elements per patch (useful for reading/writing) */

    uint* nodesPerPatch;
    

    
    // Buffers

    /** Scalar send buffer */
    
    scalar** sbuf;   


    /** Scalar receive buffer */
    
    scalar** rbuf;   

    
    /** Vector send buffer */
    
    scalar** vsbuf;   

    
    /** Vector receive buffer */
    
    scalar** vrbuf;



    /** Grid node level */

    uint* level;
    
    
} mpiInfo;

#endif // MPIINFO_H
