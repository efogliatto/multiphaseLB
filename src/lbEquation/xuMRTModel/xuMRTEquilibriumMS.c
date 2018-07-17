#include <xuMRTEquilibriumMS.h>
#include <basic.h>

void xuMRTEquilibriumMS( latticeMesh* mesh, macroFields* mfields, scalar* m_eq, uint id ) {
    


    if(mesh->lattice.model == D3Q15) {



	scalar U[3] = { mfields->U[id][0], mfields->U[id][1], mfields->U[id][2] };

	scalar rho = mfields->rho[id];
	
	scalar umag = vectorMag2(U);

		

	
	// Compute equilibrium in momentum space
	
	m_eq[0]  = rho;
	
	m_eq[1]  = rho * (-1.0 + umag);

	m_eq[2]  = rho * (1.0 - 5.0*umag);

	m_eq[3]  = rho * U[0];

	m_eq[4]  = rho * -7.0 * U[0] / 3.0;

	m_eq[5]  = rho * U[1];

	m_eq[6]  = rho * -7.0 * U[1] / 3.0;

	m_eq[7]  = rho * U[2];

	m_eq[8]  = rho * -7.0 * U[2] / 3.0;

	m_eq[9]  = rho * ( 2.0 * U[0] * U[0]  -  U[1] * U[1]  -  U[2] * U[2] );

	m_eq[10] = rho * ( U[1] * U[1]  -  U[2] * U[2] );

	m_eq[11] = rho * U[0]*U[1];

	m_eq[12] = rho * U[1]*U[2];

	m_eq[13] = rho * U[0]*U[2];

	m_eq[14] = 0;

	

    }

}
