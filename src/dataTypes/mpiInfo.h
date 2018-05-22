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

typedef struct {
    
    unsigned int pid;   /**< Process id */
    
    unsigned int worldSize;   /**< Total number of processes */
    
    unsigned int nghosts;   /**< Total number of ghosts */
    
    unsigned int nlocal;   /**< Number of local elements */
    
    unsigned int** recvGhosts;   /**< Receive ghosts indices*/
    
    unsigned int** sendGhosts;   /**< Send ghosts indices*/        
    
    unsigned int* nrg;   /**< Number of receive ghosts */
    
    unsigned int* nsg;   /**< Number of send ghosts */
    

    // Buffers

    /* // Scalars */
    /* double* scalarSendBuff; */
    /* double* scalarRecvBuff; */
    /* int* sendScalarBlocks; */
    /* int* recvScalarBlocks; */

    double** sbuf;   /**< Scalar send buffer */
    
    double** rbuf;   /**< Scalar receive buffer */

    double** vsbuf;   /**< Vector send buffer */
    
    double** vrbuf;   /**< Vector receive buffer */
    
    
} mpiInfo;

#endif // MPIINFO_H
