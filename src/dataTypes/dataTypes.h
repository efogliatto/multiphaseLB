#ifndef DATATYPES_H
#define DATATYPES_H


/**
 * @file dataTypes.h
 * @author Ezequiel O. Fogliatto
 * @date 26 Apr 2018
 * Basic pre-defined constants and data types
 */

/** Unsigned int short name */

typedef unsigned int uint;


/** Scalar for precision change */

typedef double scalar;


/** Field creation options */

typedef enum {

    MUST_READ,
    
    NO_READ    

} fieldOpt;


#endif // DATATYPES_H
