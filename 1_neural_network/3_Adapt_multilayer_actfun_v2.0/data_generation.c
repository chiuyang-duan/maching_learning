#include "Common.h"

/*
study aim:
    y<x && y>0 && x<5
input:
    data_x   
    data_y
aim in triangle:
    data_out1 = 0.9;
    data_out2 = -0.9;
*/



struct neural_context * input_data = NULL;

void study_data1_result()
{
    printf("                             \n");
    printf("       |        .    .       \n");
    printf("       |        .  .         \n");
    printf("       5      (5,5)          \n");
    printf("       |       ..            \n");
    printf("       |     .++.            \n");
    printf("       |   .++++.            \n");
    printf("       | .++++++.            \n");
    printf("-------0--------5------------\n");
    printf("     . |        .            \n");
    printf("   .   |        .            \n");
    printf(" .     |        .            \n");    
    printf("          study aim:         \n");
    printf("       y<x && y>0 && x<5.    \n");       
}

struct neural_layer * make_study_data1()
{

    int i;
    LEARN_LOG("make_study_data1\n");
    printf("       y<x && y>0 && x<5.    \n"); 
    
    for(i = 0;i<TEST_NUM;i++)
    {
        data_x[0][i] = rand_num(10);
        data_x[1][i] = rand_num(10);
        
        if((data_x[1][i] < data_x[0][i])&&(data_x[1][i] > 0)&&(data_x[0][i] < 5))
        {
           data_out[0][i] = 0.9;
           data_out[1][i] = 0.01;
        }
        else
        {
            data_out[0][i] = 0.01;
            data_out[1][i] = 0.9;
        }
    }    
}
void study_data2_result()
{
    printf("                 . ++++++++++\n");
    printf("       |       . ++++++++++++\n");
    printf("       |     . ++++++++++++ .\n");
    printf("       5   . ++++++++++++ .  \n");
    printf("       | . ++++++++++++ .    \n");
    printf("       3 ++++++++++++ .      \n");
    printf("     . |+++++++++++ .        \n");
    printf("   . ++|+++++++++ .          \n");
    printf("-------0--------5------------\n");
    printf(". +++++|+++++ .              \n");
    printf(" ++++++|+++ .                \n");
    printf(" ++++++|+ .                  \n");    
    printf("          study aim:         \n");
    printf("       y<x && y>0 && x<5.    \n");       
}

void make_study_data2()
{

    int i;
    LEARN_LOG("make_study_data1\n");
    printf("y < (x + 3) && y > (x-5)");
    for(i = 0;i<TEST_NUM;i++)
    {
        data_x[0][i] = rand_num(10);
        data_x[1][i] = rand_num(10);
        
        if((data_x[1][i] < (data_x[0][i] + 3))&&(data_x[1][i] > (data_x[0][i] - 5)))
        {
            data_out[0][i] = 0.9;
            data_out[1][i] = 0.01;
        }
        else
        {
            data_out[0][i] = 0.01;
            data_out[1][i] = 0.9;
        }
    }    
}
struct neural_arg * set_input_data_arg()
{
    int i;
    int OUTPUT_LAYER;
    
    struct neural_arg * obj = kzalloc(sizeof(*obj),GFP_USER);
    LEARN_LOG("get_arch_arg+++\n");
    if(!obj){
        LEARN_ERR("alloc neural arch argument error! \n");
        return NULL;
    }
    
    printf("pls input number of input_node:");
    obj->input_node = INPUT_NODE;
    
    printf("\npls input number of output_node:");
    obj->output_node = OUTPUT_NODE;
    printf("\npls input number of hidden layer:");
    obj->hidden_layer = 0;
    
    OUTPUT_LAYER = obj->hidden_layer+1;
    
    if(NULL == (obj->node_array = (int *)malloc((obj->hidden_layer+2) * sizeof(int)))){
        LEARN_LOG("malloc error \n");
    }
    memset(obj->node_array,0,(obj->hidden_layer+2) * sizeof(int));

    obj->node_array[INPUT_LAYER] = obj->input_node;
    obj->node_array[OUTPUT_LAYER] = obj->output_node;

    
    return obj;

}

struct neural_context * input_data_context_alloc(void)
{
    struct neural_context * obj = kzalloc(sizeof(*obj),GFP_USER);
    LEARN_LOG("neural_context_alloc+++\n");
    if(!obj){
        LEARN_ERR("alloc neural context error! \n");
        return NULL;
    }
    
    obj->arg = set_input_data_arg();
    obj->layer = layers_context_alloc(obj->arg);
    obj->run = NULL;
    return obj;
}



