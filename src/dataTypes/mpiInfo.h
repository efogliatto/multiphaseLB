#ifndef MPIINFO_H
#define MPIINFO_H

#define MPI_BUFF_SIZE 100

struct mpiInfo {

    // Process id
    unsigned int pid;

    // Total number of processes
    unsigned int worldSize;    

    // Total number of ghosts
    unsigned int nghosts;

    // Local elements
    unsigned int nlocal;

    // Elements shared with other processes
    unsigned int* shared;

    // Receive ghosts
    unsigned int** recvGhosts;

    // Send ghosts
    unsigned int** sendGhosts;
    
    
    

    

    
    // Buffers

    /* // Scalars */
    /* double* scalarSendBuff; */
    /* double* scalarRecvBuff; */
    /* int* sendScalarBlocks; */
    /* int* recvScalarBlocks; */

    double** sbuf;
    
    double** rbuf;

    double** vsbuf;
    
    double** vrbuf;    
    
    
};

#endif // MPIINFO_H
