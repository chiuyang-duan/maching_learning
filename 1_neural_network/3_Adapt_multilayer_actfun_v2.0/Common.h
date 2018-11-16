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
#define HIDDEN_ONE_LAYER 1
#define INIT 0
#define LEARNING 1
#define FORECAST 2 
#define ADD_DELTA 3 
#define GET_DELTA 4

#define POSITIVE_PARTIAL_DERIVATIVES_COEFFICIENT 0.0001 
#define LEARNING_RATE 0.005
#define LEARNING_NUM 200000

#define DUMMY_NODE 1
#define DUMMY -1.0

#define DEBUG 0
#define DEBUG_POINT 0
#define DEBUG_DATA 0

#define PRINT_TEST_DATA 1

#if DEBUG
#define LEARN_LOG(...) printf("File %s, Func %s: %d > ", __FILE__, __FUNCTION__, __LINE__); \
                          printf(__VA_ARGS__);
#define LEARN_ERR(...) printf("ERR_File %s, Func %s: %d > ", __FILE__, __FUNCTION__, __LINE__); \
                          printf(__VA_ARGS__);                         
#else
#define LEARN_LOG(...)
#define LEARN_ERR(...)
#endif
#if DEBUG_POINT
#define DEPOINT_LOG(...) printf("File %s, Func %s: %d > ", __FILE__, __FUNCTION__, __LINE__); \
                          printf(__VA_ARGS__);    
#else
#define DEPOINT_LOG(...)
#endif
#if DEBUG_DATA
#define DATA_LOG(...) printf("File %s, Func %s: %d > ", __FILE__, __FUNCTION__, __LINE__); \
                          printf(__VA_ARGS__);    
#else
#define DATA_LOG(...)
#endif



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
    int (*run)(struct neural_context * ,struct neural_context * , int); 
    int (*result_print)(struct neural_context * );
};

int neural_result_print(struct neural_context * );
struct neural_layer * layers_context_alloc(struct neural_arg * );
struct neural_node * node_context_alloc(struct neural_arg * ,int );
struct neural_arg * get_arch_arg(void);
struct neural_layer * get_last_layer(struct neural_context * );
double act_squashing_function(double );
double rand_num(double max);
double act_squashing_function(double x);


#endif
