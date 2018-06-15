#ifndef MPIINFO_H
#define MPIINFO_H

#define MPI_BUFF_SIZE 500  /**< MPI buffer size */

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
    
    uint pid;   /**< Process id */
    
    uint worldSize;   /**< Total number of processes */
    
    uint nghosts;   /**< Total number of ghosts */
    
    uint nlocal;   /**< Number of local elements */
    
    uint** recvGhosts;   /**< Receive ghosts indices*/
    
    uint** sendGhosts;   /**< Send ghosts indices*/        
    
    uint* nrg;   /**< Number of receive ghosts */
    
    uint* nsg;   /**< Number of send ghosts */
    

    // Buffers

    /* // Scalars */
    /* double* scalarSendBuff; */
    /* double* scalarRecvBuff; */
    /* int* sendScalarBlocks; */
    /* int* recvScalarBlocks; */

    scalar** sbuf;   /**< Scalar send buffer */
    
    scalar** rbuf;   /**< Scalar receive buffer */

    scalar** vsbuf;   /**< Vector send buffer */
    
    scalar** vrbuf;   /**< Vector receive buffer */
    
    
} mpiInfo;

#endif // MPIINFO_H
