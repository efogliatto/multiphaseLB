#ifndef LITEMPMRTCOLLISION_H
#define LITEMPMRTCOLLISION_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

/**
 * @file liTempMRTCollision.h
 * @author Ezequiel O. Fogliatto
 * @date 14 Dic 2017
 * @brief MRT collision for energy equation
 */



/**
 * @brief MRT Collision for energy equation
 *
 * This function performs an MRT-based collision for energy equation
 * 
 * The post collision process produces
 * \f$ \mathbf{g^*}(\mathbf{x},t) = \mathbf{M}^{-1} \left[ \mathbf{n}(\mathbf{x},t) - \mathbf{Q}(\mathbf{n} - \mathbf{n}^{(eq)})_{(\mathbf{x},t)} + \left( \mathbf{I} - \frac{1}{2}\mathbf{Q} \right) \mathbf{\hat{\Gamma}} \right] \f$
 * @param mesh Lattice mesh struct.
 * @param mfields Macroscopic fields struct.
 * @param field Population field to be collided
 * @return Nothing. Updates @p field with post-collision values
 */

void liTempMRTCollision( latticeMesh* mesh, macroFields* mfields, lbeField* field );

#endif // LITEMPMRTCOLLISION_H
