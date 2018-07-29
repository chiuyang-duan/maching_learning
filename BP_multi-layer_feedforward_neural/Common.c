#include "Common.h"
#include <math.h>


float act_squashing_function(float x)
{
	return (1/(1+(exp(-x))));
}

float act_step_function(float x)
{
	if(0 <= x)
		return 1;
	return 0;
}











