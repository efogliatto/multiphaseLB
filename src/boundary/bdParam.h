#ifndef BDPARAM_H
#define BDPARAM_H

#include <fixedTParam.h>
#include <fixedRandomTParam.h>
#include <fixedUParam.h>
#include <uHeatFluxParam.h>
#include <fixedEOSpParam.h>

typedef union {

    fixedTParam ft;

    fixedRandomTParam frdt;    

    fixedUParam fu;

    uHeatFluxParam uhf;

    fixedEOSpParam fep;

} bdParam;

#endif // BDPARAM_H
