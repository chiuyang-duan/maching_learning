#include "Common.h"

double act_squashing_function(double x)
{
	return (1/(1+(exp(-x))));
}

double act_step_function(double x)
{
	if(0 <= x)
		return 1;
	return 0;
}











