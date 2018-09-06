#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>

#define POSITIVE_PARTIAL_DERIVATIVES_COEFFICIENT 0.001 
#define INPUT_LAYER 0
#define HIDDEN_ONE_LAYER 1;
#define INIT 0
#define LEARNING 1
#define FORECAST 2 
#define ADD_DELTA 3 
#define GET_DELTA 4

struct neural_node 
{
    double *weight;
    double *delta_weight;
    double out;   
    struct neural_node * prev_node;
    struct neural_node * next_node;
};

struct neural_layer
{
    struct neural_node * node; 
    struct neural_layer * prev_layer;
    struct neural_layer * next_layer;
};

struct neural_arg{
    int input_node;
    int output_node;
    int hidden_layer;
    int * node_array;
};
struct neural_context
{
    struct neural_arg * arg;
    struct neural_layer * layer;
    int (*run)(struct neural_arg * ,struct neural_layer *, int status);   
};

#endif
