/*
Calculation of I-V characteristic for TBRTD
2016/06/22
Masahiro Fukuoka
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

const double e = 1.60217662e-19;
const double k_B = 1.38064852e-23;

// gamma_g
double calc_gamma_g(double sigma)
{
	return 2*sigma*sqrt(2*log(2.0));
}

// gamma
double calc_gamma(double sigma, double gamma_l)
{
	double gamma_g = calc_gamma_g(sigma);
	return pow(pow(gamma_g, 5) + 2.69269*pow(gamma_g, 4)*gamma_l + 2.42843*pow(gamma_g, 3)*pow(gamma_l, 2) + 4.47163*pow(gamma_g, 2)*pow(gamma_l, 3) + 0.07842*gamma_g*pow(gamma_l, 4) + pow(gamma_l, 5), 1/3);
}

// xi
double calc_xi(double sigma, double gamma_l)
{
	double gamma = calc_gamma(sigma, gamma_l);
	return 1.36603(gamma_l/gamma) -0.47719*pow((gamma_l/gamma), 2) +0.1116*pow((gamma_l/gamma), 3);
}

// thermionic-type of current density
double j_thermal(double v, double T, double J_e, double V_e, double n)
{
	double tmp1 = exp((e*v)/(n*k_B*T)) - 1.0;
	double tmp2 = exp((e*V_e)/(n*k_B*T)) - 1.0;
	return J_e * tmp1 / tmp2;
}

// Gaussian
double gaussian(double x, double x0, double sigma)
{
	
}

// Lorentzian
double lorentzian(double x, double x0, double gamma_l)
{
	
}