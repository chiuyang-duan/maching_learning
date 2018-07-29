#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdio.h>
#include <math.h>

struct study_data{
int input_node_num;
int output_node_num;
float * input_data;
float * output_data;
};
struct input_floor{
int node_num;
float * input_data;

};

float act_squashing_function(float x);
float act_step_function(float x);

 
#endif
