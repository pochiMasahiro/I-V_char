#ifndef _STDIO
#define _STDIO

#include <stdio.h>

#endif
#ifndef _STDLIB
#define _STDLIB

#include <stdlib.h>

#endif
#ifndef _PARAMETER_PERSER
#define _PARAMETER_PERSER

#include "parameter_parser.h"

#endif

#ifndef _I_V_CHAR
#define _I_V_CHAR

#include "i-v_char.h"

#endif

int main(void)
{
	TBRTDproperties prp = parameter();
	
  double i;
	for(i=0; i < 0.4; i+=0.0002) {
		fprintf(stdout, "%E %E\n", i, j_tbrtd(i, prp));
	}
	return EXIT_SUCCESS;
}
