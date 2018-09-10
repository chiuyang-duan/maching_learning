#include "Common.h"
void rand_init()
{
    LEARN_LOG("rand_init\n");
    srand((int)time(0)); 
}
double rand_num(double max)
{
	double rand1;
    LEARN_LOG("rand_num\n");
	rand1 = (((double)(rand()%1000)/1000.0 * (2 * max)) - max);
    return rand1;
}

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

struct neural_layer * get_last_layer(struct neural_context * temp_neural)
{
    struct neural_layer * obj_last_layer = NULL;
    obj_last_layer = temp_neural->layer;
    while(NULL != obj_last_layer->next_layer){
        obj_last_layer = obj_last_layer->next_layer;
    }
    return obj_last_layer;
}

struct neural_arg * get_arch_arg(void)
{
    int i;
    int OUTPUT_LAYER;
    
    struct neural_arg * obj = (struct neural_arg *)malloc(sizeof(*obj));
    LEARN_LOG("get_arch_arg+++\n");
    if(!obj){
        LEARN_ERR("alloc neural arch argument error! \n");
        return NULL;
    }
    
    printf("pls input number of input_node:");
    scanf("%d",&obj->input_node);
    
    printf("pls input number of output_node:");
    scanf("%d",&obj->output_node);
    printf("pls input number of hidden layer:");
    scanf("%d",&obj->hidden_layer);
    
    OUTPUT_LAYER = obj->hidden_layer+1;
    
    if(NULL == (obj->node_array = (int *)malloc((obj->hidden_layer+2) * sizeof(int)))){
        LEARN_ERR("malloc error \n");
    }
    memset(obj->node_array,0,(obj->hidden_layer+2) * sizeof(int));


    obj->node_array[INPUT_LAYER] = obj->input_node;
    for(i = 1; i < OUTPUT_LAYER; i++){
        printf("\npls input %d_layer_node_num:",i+1);
        scanf("%d",&obj->node_array[i]);
    }
    obj->node_array[OUTPUT_LAYER] = obj->output_node;

#if DEBUG
    LEARN_LOG("arg success \n");
    for(i = 0; i < OUTPUT_LAYER+1; i++){
        LEARN_LOG("obj->node_array[%d]=%d",i,obj->node_array[i]);
    }
#endif    

    return obj;
}

struct neural_node * node_context_alloc(struct neural_arg * arg,int num_current_layer)
{
    int i;
    int NUM_ALL_LAYER = arg->hidden_layer + 2;  
    struct neural_node * head = NULL;
    
    struct neural_node * obj = (struct neural_node *)malloc(sizeof(*obj));
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
        obj->next_node = (struct neural_node *)malloc(sizeof(struct neural_node));
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
            obj->weight = (double *)malloc(arg->node_array[num_current_layer-1] * sizeof(double));
            if(!obj->weight){
                LEARN_ERR(" alloc weight error ! \n");
                return NULL;
            }          
            obj->delta_weight = (double *)malloc(arg->node_array[num_current_layer-1] * sizeof(double));
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
    struct neural_layer * obj = (struct neural_layer *)malloc(sizeof(*obj));
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
        obj->next_layer = (struct neural_layer *)malloc(sizeof(struct neural_layer));
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

int neural_result_print(struct neural_context * temp_neural)
{
    int count = 0;
    struct neural_layer * last_layer;
    struct neural_node * obj_node;
    last_layer = get_last_layer(temp_neural);
    obj_node = last_layer->node;
    while(NULL != obj_node->next_node){
        obj_node = obj_node->next_node;
        printf("out%d:%lf ",count,obj_node->out);
        count++; 
    }
    printf("\n");
    return 0;
}


