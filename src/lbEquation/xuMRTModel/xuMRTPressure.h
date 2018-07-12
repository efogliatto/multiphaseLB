#ifndef XUMRTPRESSURE_H
#define XUMRTPRESSURE_H

#include <latticeMesh.h>
#include <lbeField.h>

scalar xuMRTPressure( latticeMesh* mesh, lbeField* field, scalar* rho, scalar* T, scalar sigma, uint id );

#endif // XUMRTPRESSURE_H
