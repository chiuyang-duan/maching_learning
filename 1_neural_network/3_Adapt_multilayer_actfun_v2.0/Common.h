#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>

struct neural_arch{
    int input_node_num;
    int output_node_num;
    int hidden_layer_num;
    int * hidden_layer_node_num;
    void (*get_arg)(struct * neural_arch);
    
};

#endif
