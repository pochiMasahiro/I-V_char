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

const double e = 1.602e-19;
const double k_B = 1.38e-23 / e;
const double m_ = (9.11e-31)*0.0041;
const double h_ = 1.05e-34;


// electron suppling
double supply(double E_z, double v, double T, double E_F, double E_c)
{
	double tmp1 = (pow(e, 2)*m_*k_B*T)/(2*pow(M_PI, 2)*pow(h_, 3));
	double tmp2 = 1.0 + exp((E_F-E_c)/(k_B*T));
	double tmp3 = 1.0 + exp((E_F-(E_z-E_c+v))/(k_B*T));
	return tmp1*log(tmp2/tmp3);
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
double t_res(double E_z, double V, double gamma_l, double sigma)
{
	double xi = calc_xi(sigma, gamma_l);
	return xi*lorentzian(E_z, V, gamma_l) + (1.0 - xi)*gaussian(E_z, V, sigma);
}

double t_res_integral(double V, double gamma_l, double sigma)
{
	double xi = calc_xi(sigma, gamma_l);
	return (1.0-xi)/M_SQRT2 + (xi/M_PI)*(M_PI_2+atan2(-2.0*V,gamma_l));
}

// thermionic-type of current density
double j_thermal(double v, double T, double J_e, double V_e, double n)
{
	double tmp1 = exp(v/(n*k_B*T)) - 1.0;
	double tmp2 = exp(V_e/(n*k_B*T)) - 1.0;
	return J_e * tmp1 / tmp2;
}

double E_r(double V)
{
	double E_r0 = 97.2e-3;
	double eta_r = 0.71;
	return E_r0 - (eta_r*V);
}
long double E_l(double V)
{
	double E_l0 = 44.7e-3;
	double eta_l = 0.353;
	return E_l0 - (eta_l*V);
}

int main(void)
{
	double V_e = 0.36;
	double I_e = 0.60e-3;
	double T = 100;
	double n = 3.7;
	double sigma = 18.0e-3;
	double gamma_l = 16.0e-3;
	double E_F = 40e-3;
	double E_c = 0.0;
	
	double i;
	double tbrtd = 0.0;
	double j_rtd = 0.0;
	double j_rtd_l = 0.0;
	double j_rtd_r = 0.0;
	double j_th = 0.0;
	fprintf(stdout, "V, j_rtd_l, j_rtd_r, j_rtd, j_th\n");       
	for(i=0; i < 0.4; i+=0.0002) {
		j_rtd_l = supply(E_l(i), i, T, E_F, E_c)*t_res(E_l(i), E_r(i), gamma_l, sigma)*t_res_integral(E_l(i), gamma_l, sigma);
		j_rtd_r = supply(E_r(i), i, T, E_F, E_c)*t_res(E_r(i), E_l(i), gamma_l, sigma)*t_res_integral(E_r(i), gamma_l, sigma);
		j_rtd = (j_rtd_l + j_rtd_r) * 3.0e-28;
		j_th = j_thermal(i, T, I_e, V_e, n) * 3e6;
		tbrtd = j_rtd + j_th;
		fprintf(stdout, "%E %E %E %E %E %E\n", i, j_rtd_l, j_rtd_r, j_rtd, j_th, tbrtd);
	}
	return EXIT_SUCCESS;
}
