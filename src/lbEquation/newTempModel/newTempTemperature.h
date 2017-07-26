#ifndef NEWTEMPTEMPERATURE_H
#define NEWTEMPTEMPERATURE_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

double newTempTemperature( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int id );

#endif // NEWTEMPTEMPERATURE_H
