#include <stdio.h>
#include <stdlib.h>
#include "parameter_parser.h"
#include "i-v_char.h"

int main(void)
{
	TBRTDproperties prp = parameter();
	
  double i;
	for(i=0; i < 1.2; i+=0.002) {
		fprintf(stdout, "%E %E\n", i, j_tbrtd(i, prp));
	}
	return EXIT_SUCCESS;
}
