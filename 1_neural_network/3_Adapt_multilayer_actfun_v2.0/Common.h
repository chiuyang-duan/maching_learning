#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>

#define INPUT_LAYER 0
#define HIDDEN_ONE_LAYER 1;

struct neural_node 
{
    double *weight;
    double *delta_weight;
    double out;   
    struct neural_node * next_node;
};

struct neural_layer
{
    struct neural_node * node; 
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
    int (*init)(struct neural_arg * ,struct neural_layer *);
    int (*run)(struct neural_arg * ,struct neural_layer *);   
    int (*get_delta)(struct neural_arg *);
    int (*para_iteration)(struct neural_arg *);
};

#endif
