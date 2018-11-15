#include "Common.h"
#include "data_generation.h"
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

int make_study_data1(struct neural_context * input_data)
{
    int i;
    double data_x[2];
    double data_out[2];
    LEARN_LOG("make_study_data1\n");
    printf("       y<x && y>0 && x<5.    \n"); 
    data_x[0] = rand_num(5.0);
    data_x[1] = rand_num(5.0);
    //DATA_LOG("data_x[0]=%lf, data_x[1]=%lf\n",data_x[0],data_x[1]);
    if((data_x[0] >= -2)&&(data_x[0] <= 2))
    //if((data_x[1] <= data_x[0])&&(data_x[1] >= -2)&&(data_x[0] <= 3))
    {
       data_out[0] = 1;
       data_out[1] = 0;
    }
    else
    {
        data_out[0] = 0;
        data_out[1] = 1;
    }
    
    input_data->layer->next_layer->node->next_node->out = data_x[0];
    input_data->layer->next_layer->node->next_node->next_node->out = data_x[1];

    input_data->layer->next_layer->next_layer->node->next_node->out = data_out[0];
    input_data->layer->next_layer->next_layer->node->next_node->next_node->out = data_out[1];   

    return 0;
}
#if 0
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
#endif
struct neural_arg * set_input_data_arg()
{
    int i;
    int OUTPUT_LAYER;
    
    struct neural_arg * obj = (struct neural_arg *)malloc(sizeof(*obj));
    LEARN_LOG("get_arch_arg+++\n");
    if(!obj){
        LEARN_ERR("alloc neural arch argument error! \n");
        return NULL;
    }
    
    printf("set_input_data_arg  obj->input_node = INPUT_NODE;\n");
    obj->input_node = INPUT_NODE + DUMMY_NODE;    
    printf("set_input_data_arg  obj->output_node = OUTPUT_NODE;\n");
    obj->output_node = OUTPUT_NODE;
    printf("set_input_data_arg  obj->hidden_layer = 0;\n");
    obj->hidden_layer = 0;
    
    OUTPUT_LAYER = obj->hidden_layer+1;
    
    if(NULL == (obj->node_array = (int *)malloc((obj->hidden_layer+2) * sizeof(int)))){
        LEARN_LOG("malloc error \n");
    }
    memset(obj->node_array,0,(obj->hidden_layer+2) * sizeof(int));
    LEARN_LOG("malloc obj->node_array %d\n",(obj->hidden_layer+2));

    obj->node_array[INPUT_LAYER] = obj->input_node;
    obj->node_array[OUTPUT_LAYER] = obj->output_node;

    
    return obj;

}
double x = -5.5;
double y = 5;
int run_get_input_data(struct neural_context * neural,struct neural_context * data_list, int status)
{


    if(TEST_DATA == status){

        x = x + 0.5;  
        if(x>=5)
        {
            y = y - 0.5;
            x = -5;
            
        }
        if(x == -5)
        {
            printf("\n");
        }        
       // printf("%1.1lf,%1.1lf ",x,y);
    }else{
        printf("\n pls input test data x,y\n");
        scanf("%lf,%lf",&x,&y);
    }
    neural->layer->next_layer->node->next_node->out = x;
    neural->layer->next_layer->node->next_node->next_node->out = y;
    return 0;
}




