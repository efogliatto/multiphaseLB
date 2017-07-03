#ifndef LITEMPTEMPERATURE_H
#define LITEMPTEMPERATURE_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

double liTempTemperature( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int id );

#endif // LITEMPTEMPERATURE_H
