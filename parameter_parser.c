/*
 * perser of TBRTD parameter file
 * Masahiro Fukuoka
 * 2016/07/15
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "i-v_char.h"

// Physics parameter
const double k_b = 1.38e-23;
const double e = 1.602e-19;
const double m0 = 9.11e-31;
const double hbar = 1.05e-34;

TBRTDproperties parameter()
{
	FILE *fp;
  char filename[255];
	char str[255];
	char name[255];
	char dummy[8];
	char value[255];
	TBRTDproperties prp;
	double m_star;

  fgets(filename, 254, stdin);
  printf("%s\n", filename);
  filename[strlen(filename)] = '\0';
	if ((fp = fopen( filename, "r" )) == NULL) {
		fprintf( stderr, "File open error");
		exit(EXIT_FAILURE);
	}
	
	while (fgets(str, 255, fp) != NULL) {
		if ((str[0] == '#') || (str[0] == '\n')) ;
		else {
			sscanf(str, "%s %s %s", name, dummy, value);
			if (!strcmp(name, "V_e")) prp.V_e = strtod(value, NULL);
			if (!strcmp(name, "J_e")) prp.J_e = strtod(value, NULL);
			if (!strcmp(name, "T")) prp.T = strtod(value, NULL);
			if (!strcmp(name, "n")) prp.n = strtod(value, NULL);
			if (!strcmp(name, "sigma")) prp.sigma = strtod(value, NULL);
			if (!strcmp(name, "gamma_l")) prp.gamma_l = strtod(value, NULL);
			if (!strcmp(name, "E_F")) prp.E_F = strtod(value, NULL);
			if (!strcmp(name, "E_l0")) prp.E_l0 = strtod(value, NULL);
			if (!strcmp(name, "E_r0")) prp.E_r0 = strtod(value, NULL);
			if (!strcmp(name, "Eta_l")) prp.Eta_l = strtod(value, NULL);
			if (!strcmp(name, "Eta_r")) prp.Eta_r = strtod(value, NULL);
			if (!strcmp(name, "area")) prp.area = strtod(value, NULL);
      if (!strcmp(name, "m*")) m_star = strtod(value, NULL); 
			if (!strcmp(name, "hbar")) prp.hbar = strtod(value, NULL);
			if (!strcmp(name, "constA")) prp.constA = strtod(value, NULL);
			if (!strcmp(name, "constB")) prp.constB = strtod(value, NULL);
		}
	}

  prp.hbar = hbar;
  prp.e = e;
  prp.k_B = k_b / e;
  prp.m = m0 * m_star;
  prp.xi = calc_xi(prp.sigma, prp.gamma_l);
  fclose(fp);

	return prp;
}
