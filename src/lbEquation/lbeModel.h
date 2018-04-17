#ifndef LBEMODEL_H
#define LBEMODEL_H

typedef enum {

    /** Li et al. MRT pseudopotential model for two-phase Navier Stokes*/
    liMRT,

    /** 
	My MRT model for energy equation in two-phase fluid under pseudopotential formulation.
	Under development
    */
    myMRT
    
} lbeModel;

#endif // LBEMODEL_H
