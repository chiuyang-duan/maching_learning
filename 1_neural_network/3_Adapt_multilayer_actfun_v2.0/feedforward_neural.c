#include "Common.h"


#define DEBUG 1
#if DEBUG
#define LEARN_LOG(...) printf("Filename %s, Function %s, Line %d > ", __FILE__, __FUNCTION__, __LINE__); \
                          printf(__VA_ARGS__); \
                          printf("\n");
#define LEARN_ERR(...) printf("ERR_Filename %s, Function %s, Line %d > ", __FILE__, __FUNCTION__, __LINE__); \
                          printf(__VA_ARGS__); \
                          printf("\n");

#else
#define LEARN_LOG(...)
#define LEARN_ERR(...)

#endif

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

struct neural_node * get_node(struct neural_arg * arg,int num_current_layer)
{
//    int OUTPUT_LAYER = arg->hidden_layer + 1;
    int i;
    int NUM_ALL_LAYER = arg->hidden_layer + 2;  
    
    struct neural_node * obj = kzalloc(sizeof(*obj),GFP_USER);
    LEARN_LOG("layers_context_alloc+++\n");
    if(!obj){
        LEARN_ERR("alloc layers context error! \n");
        return NULL;
    }  

    
    if(INPUT_LAYER == num_current_layer){    
        obj->weight = NULL;
        obj->delta_weight = NULL;
    }
    else if(HIDDEN_ONE_LAYER == num_current_layer){
        obj->weight = kzalloc(arg->input_node * sizeof(double),GFP_USER);
        if(!obj->weight){
            LEARN_ERR(" alloc weight error ! \n");
            return NULL;
        }  
        obj->delta_weight = kzalloc(arg->input_node * sizeof(double),GFP_USER); 
        if(!obj->delta_weight){
            LEARN_ERR(" alloc delta weight error ! \n");
            return NULL;
        }          
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

    

    
    
    return obj;
}


struct neural_layer * layers_context_alloc(struct neural_arg * arg)
{
    int i;
    struct neural_layer * obj = NULL;
    int NUM_ALL_LAYER = arg->hidden_layer + 2; 
    for(i = 0; i < NUM_ALL_LAYER; i++)
    {
        obj = kzalloc(sizeof(*obj),GFP_USER);
        LEARN_LOG("layers_context_alloc+++\n");
        if(!obj){
            LEARN_ERR("alloc layers context error! \n");
            return NULL;
        }  
        obj->next_layer = NULL;
        obj->node = get_node(arg,i);
    }
    
    return obj;
}

struct neural_context * ne = NULL;
struct neural_context * neural_context_alloc(void)
{
    struct neural_context * obj = kzalloc(sizeof(*obj),GFP_USER);
    LEARN_LOG("neural_context_alloc+++\n");
    if(!obj){
        LEARN_ERR("alloc neural context error! \n");
        return NULL;
    }
    obj->arg =  get_arch_arg();
    obj->layer = layers_context_alloc(obj->arg);
    
    return obj;
}

int main()
{ 
    ne = neural_context_alloc();    

    
	return 0;
}


 
