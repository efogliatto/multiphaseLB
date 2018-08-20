#ifndef LBEMODEL_H
#define LBEMODEL_H

typedef enum {

    /** Li et al. MRT pseudopotential model for two-phase Navier Stokes in D2Q9 grids*/
    liMRT,
    
    /** 
	My MRT model for energy equation in two-phase fluid under pseudopotential formulation.
	Under development
    */
    myMRT,


    /** Xu et al. MRT pseudopotential model for two-phase Navier Stokes in D3Q15 grids*/
    xuMRT,


    liTempMRT
    
} lbeModel;

#endif // LBEMODEL_H
