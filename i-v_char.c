/*
Calculation of I-V characteristic for TBRTD
2016/06/22
Masahiro Fukuoka
*/
#include <math.h>
#include "i-v_char.h"

// electron suppling
double supply(double E_z, double v, TBRTDproperties prp)
{
	// double tmp1 = (pow(prp.e, 2) * prp.m * prp.k_B * prp.T) / (2*pow(M_PI, 2) * pow(prp.hbar, 3));
	double tmp2 = 1.0 + exp((prp.E_F - E_z) / (prp.k_B * prp.T));
	double tmp3 = 1.0 + exp((prp.E_F - E_z - v) / (prp.k_B * prp.T));
	return /*tmp1**/log(tmp2/tmp3);
}

// gamma_g
double calc_gamma_g(double sigma)
{
	return 2*sigma*sqrt(2*log(2.0));
}

// gamma
double calc_gamma(double sigma, double gamma_l)
{
	double gamma_g = calc_gamma_g(sigma);
	return pow(pow(gamma_g, 5) + 2.69269*pow(gamma_g, 4)*gamma_l + 2.42843*pow(gamma_g, 3)*pow(gamma_l, 2) + 4.47163*pow(gamma_g, 2)*pow(gamma_l, 3) + 0.07842*gamma_g*pow(gamma_l, 4) + pow(gamma_l, 5), 1/5);
}

// xi
double calc_xi(double sigma, double gamma_l)
{
	double gamma = calc_gamma(sigma, gamma_l);
	return 1.36603*(gamma_l/gamma) -0.47719*pow((gamma_l/gamma), 2) +0.11116*pow((gamma_l/gamma), 3);
}

// Gaussian
double gaussian(double x, double x0, double sigma)
{
	return (1.0/(sigma*sqrt(2.0*M_PI)))*exp(-1.0 * pow(x-x0, 2.0) / (2.0*pow(sigma, 2.0)));
}

// Lorentzian
double lorentzian(double x, double x0, double gamma_l)
{
	return (gamma_l/(2.0*M_PI)) * ( 1.0 / ( pow(x-x0, 2.0) + pow(gamma_l/2.0, 2.0) ) );
}

// transmission probability
double t_res(double E_z, double V, TBRTDproperties prp)
{
	return prp.xi * lorentzian(E_z, V, prp.gamma_l) + (1.0 - prp.xi)*gaussian(E_z, V, prp.sigma);
}

double t_res_integral(double V, TBRTDproperties prp)
{
	return (1.0-prp.xi) / M_SQRT2 + (prp.xi / M_PI) * (M_PI_2 + atan2(-2.0 * V, prp.gamma_l));
}

// thermionic-type of current density
double j_thermal(double v, TBRTDproperties prp)
{
	// double tmp1 = exp(v/(prp.n * prp.k_B * prp.T)) - 1.0;
	double tmp2 = exp(v / (prp.n * prp.k_B * prp.T)) - 1.0;
	return prp.constC * tmp2;
}

double E_r(double V, TBRTDproperties prp)
{
	return prp.E_r0 - (prp.Eta_r * V);
}
double E_l(double V, TBRTDproperties prp)
{
	return prp.E_l0 - (prp.Eta_l * V);
}

double j_tbrtd(double v, TBRTDproperties prp)
{
	double j_rtd_l = supply(E_l(v, prp), v, prp)*t_res(E_l(v, prp), E_r(v, prp), prp)*t_res_integral(E_l(v, prp), prp);
	double j_rtd_r = supply(E_r(v, prp), v, prp)*t_res(E_r(v, prp), E_l(v, prp), prp)*t_res_integral(E_r(v, prp), prp);
	double j_th = j_thermal(v, prp);
	return prp.Const * (j_th + j_rtd_l + j_rtd_r) * prp.area;
}
