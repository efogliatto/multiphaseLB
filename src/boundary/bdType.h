#ifndef BDTYPE_H
#define BDTYPE_H

typedef enum {

    /** Bounce-back */
    bback,

    /** Fixed Temperature */
    ft,

    /** Fixed random Temperature */
    frdt,
    
    /** Fixed Velocity */    
    fu,

    /** Uniform heat flux */
    uhf,

    /** Fixed EOS pressure */
    fep,

    /** Outflow */
    of,

    /** Periodic */
    periodic

} bdType;

#endif // BDTYPE_H
