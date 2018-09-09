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


struct neural_arg * get_arch_arg(void)
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
    scanf("%d",&obj->input_node);
    
    printf("\npls input number of output_node:");
    scanf("%d",&obj->output_node);
    printf("\npls input number of hidden layer:");
    scanf("%d",&obj->hidden_layer);
    
    OUTPUT_LAYER = obj->hidden_layer+1;
    
    if(NULL == (obj->node_array = (int *)malloc((obj->hidden_layer+2) * sizeof(int)))){
        LEARN_LOG("malloc error \n");
    }
    memset(obj->node_array,0,(obj->hidden_layer+2) * sizeof(int));


    obj->node_array[INPUT_LAYER] = obj->input_node;
    for(i = 1; i < OUTPUT_LAYER; i++){
        printf("\npls input %d_layer_node_num:",i+1);
        scanf("%d",&obj->node_array[i]);
    }
    obj->node_array[OUTPUT_LAYER] = obj->output_node;

    
    return obj;
}

struct neural_node * node_context_alloc(struct neural_arg * arg,int num_current_layer)
{
    int i;
    int NUM_ALL_LAYER = arg->hidden_layer + 2;  
    struct neural_node * head = NULL;
    
    struct neural_node * obj = kzalloc(sizeof(*obj),GFP_USER);
    LEARN_LOG("layers_context_alloc+++\n");
    if(!obj){
        LEARN_ERR("alloc layers context error! \n");
        return NULL;
    }  
    obj->delta_weight = NULL;
    obj->out = 0;
    obj->weight = NULL;
    obj->next_node = NULL;
    obj->prev_node = NULL;
    head = obj;
    
    
    for(i = 0; i < arg->node_array[num_current_layer]; i++)
    {
        obj->next_node = kzalloc(sizeof(*obj),GFP_USER);
        if(!obj->next_node){
            LEARN_ERR("alloc layers context error! \n");
            return NULL;
        }
        obj->next_node->prev_node = obj;
        obj = obj->next_node;
        obj->next_node = NULL;
        
        if(INPUT_LAYER == num_current_layer){    
            obj->weight = NULL;
            obj->delta_weight = NULL;
        }
        else{
            obj->weight = kzalloc(arg->node_array[num_current_layer-1] * sizeof(double),GFP_USER);
            if(!obj->weight){
                LEARN_ERR(" alloc weight error ! \n");
                return NULL;
            }          
            obj->delta_weight = kzalloc(arg->node_array[num_current_layer-1] * sizeof(double),GFP_USER);
            if(!obj->delta_weight){
                LEARN_ERR(" alloc delta weight error ! \n");
                return NULL;
            }
        }
    }
    return head;
}


struct neural_layer * layers_context_alloc(struct neural_arg * arg)
{
    int i;
    struct neural_layer * head = NULL; 
    int NUM_ALL_LAYER = arg->hidden_layer + 2; 
    struct neural_layer * obj = kzalloc(sizeof(*obj),GFP_USER);
    LEARN_LOG("layers_context_alloc+++\n");
    if(!obj){
        LEARN_ERR("alloc layers context error! \n");
        return NULL;
    }
    obj->next_layer = NULL;
    obj->node = NULL;
    head = obj;    
    obj->prev_layer = NULL;

    for(i = 0; i < NUM_ALL_LAYER; i++)
    {
        obj->next_layer = kzalloc(sizeof(*obj),GFP_USER);
        LEARN_LOG("layers_context_alloc+++\n");
        if(!obj){
            LEARN_ERR("alloc layers context error! \n");
            return NULL;
        }  
        obj->next_layer->prev_layer = obj;
        obj = obj->next_layer;
        obj->next_layer = NULL;
        obj->node = node_context_alloc(arg,i);
    }
    
    return head;
}


