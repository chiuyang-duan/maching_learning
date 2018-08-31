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

void normal_zscore(double * inputdata, int length, double * outdata)
{
    double u = 0;
    double sigma = 0; 
    double a = 0;
    int i =0;

    outdata = (double *)malloc(length*sizeof(double));     
    
    for(i = 0; i < length; i++)
    {
        u = u + inputdata[i];            
    }
    u = u / length;
    for(i = 0; i < length; i++)
    {
        a = inputdata[i] - u;
        sigma = sigma + (a * a);
    }
    sigma = sigma / length;
    for(i = 0; i < length; i++)
    {
        outdata[i] = (inputdata[i] - u) / sigma;   
    }
}


