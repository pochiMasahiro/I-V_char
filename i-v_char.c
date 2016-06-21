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

// gannma
double calc_gannma(double)

// xi
double calc_xi(double sigma, double gamma_l)
{
	double gamma = calc_gamma(sigma, gamma_l);
	return 1.36603(gamma_l/gamma) -0.47719*pow((gamma_l/gamma), 2) +0.1116*pow((gamma_l/gamma), 3);
}
