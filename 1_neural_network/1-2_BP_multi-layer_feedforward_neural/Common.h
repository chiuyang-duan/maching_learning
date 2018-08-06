#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define INPUT_NUM 2
#define OUT_NUM 2
#define HIDDEN_LAYER_NUM 4

struct delta_parameters{

    double * w;
    double * theta;
    
    double * v;
    double * gama;
    
};

struct input_data{
    double * x;
	double * y;
    int input_num; //none dummy node
    int out_num;   //none dummy node
    int hidden_layer_num;  //none dummy node
};
struct output_data{
    double * para_w;
    double * para_v;
    double * hidden_b;
    double * y;
};

float act_squashing_function(float x);
float act_step_function(float x);
void normal_zscore(double * inputdata, int length, double * outdata);

 
#endif
