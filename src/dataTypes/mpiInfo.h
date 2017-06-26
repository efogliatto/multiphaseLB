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
    int shared;

    
    
    /* // Number of ghost processes */
    /* unsigned int nGProc; */

    /* // Array of ghost processes (size = worldSize) */
    /* unsigned int* gProc; */

    /* // Number of ghost elements with each processor */
    /* unsigned int nGhostPerProc; */

    /* // ghost elements with each processor */
    /* unsigned int** ghostPerProc; */

    /* // ghost elements with each processor, using only velocity */
    /* unsigned int** nghostPerProcVel;     */

    

    

    /* // Buffers */

    /* // Scalars */
    /* double* scalarSendBuff; */
    /* double* scalarRecvBuff; */
    /* int* sendScalarBlocks; */
    /* int* recvScalarBlocks; */

    /* double** ssbuf; */
    /* double** srbuf; */
    
};

#endif // MPIINFO_H
