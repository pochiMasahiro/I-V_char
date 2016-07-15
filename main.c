#include <stdio.h>
#include <stdlib.h>
#ifndef _I_V_CHAR
#define _I_V_CHAR

#include "i-v_char.h"

#endif

int main(void)
{
	TBRTDproperties TBRTD;
	TBRTD.V_e = 0.36;
	TBRTD.J_e = 0.60e-3;
	TBRTD.T = 100;
	TBRTD.n = 3.7;
	TBRTD.sigma = 20.0e-3;
	TBRTD.gamma_l = 16.0e-3;
	TBRTD.xi = calc_xi(TBRTD.sigma, TBRTD.gamma_l);
	TBRTD.E_F = 40e-3;
	TBRTD.e = 1.602e-19;
	TBRTD.k_B = 1.38e-23/TBRTD.e;
	TBRTD.hbar = 1.05e-34;
	TBRTD.m0 = 9.11e-31;
	TBRTD.m = TBRTD.m0 * 0.0041;
	TBRTD.E_l0 = 44.7e-3;
	TBRTD.E_r0 = 97.2e-3;
	TBRTD.Eta_l = 0.353;
	TBRTD.Eta_r = 0.71;
	TBRTD.constA = 3.0e-28;
	TBRTD.constB = 3.0e6;

	double i;
	for(i=0; i < 0.4; i+=0.0002) {
		fprintf(stdout, "%E %E\n", i, j_tbrtd(i, TBRTD));
	}
	return EXIT_SUCCESS;
}
