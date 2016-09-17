#ifndef _I_V_CHAR_H
#define _I_V_CHAR_H

typedef struct  {
	double e;
	double k_B;
	double m0;
	double m;
	double hbar;
	double Eta_l;
	double Eta_r;
	double E_l0;
	double E_r0;
	double J_e;
	double V_e;
	double T;
	double n;
	double sigma;
	double gamma_l;
	double xi;
	double E_F;
	double constA;
	double constB;
	double constC;
	double Const;
	double area;
}TBRTDproperties;

// xi
double calc_xi(double sigma, double gamma_l);

// calculation of current density of TBRTD
double j_tbrtd(double v, TBRTDproperties prp);

#endif
