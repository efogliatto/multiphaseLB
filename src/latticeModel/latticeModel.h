#ifndef LATTICEMODEL_H
#define LATTICEMODEL_H


#include <latticeVelocities.h>
#include <latticeWeights.h>
#include <latticeReverseDir.h>
#include <MRTMatrix.h>
#include <MRTInvMatrix.h>
#include <ppWeights.h>
#include <cs2.h>

#include <setLatticeInfo.h>

unsigned int latticeQ( char* modelName );

unsigned int latticeD( char* modelName );


#endif // LATTICEMODEL_H
