#include "Common.h"


struct neural_context * ne = NULL;

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


int neural_run(struct neural_context * neural,struct neural_layer * data_list, int status)
{
    int i,j,k;
    struct neural_layer * obj = neural->layer;
    struct neural_layer * layer_head = neural->layer;
    struct neural_layer * last_layer = NULL;
    struct neural_node * prev_layer_node = NULL;
    struct neural_node * current_node = NULL;
    struct neural_arg * arg = neural->arg;
    
    struct neural_node *  input_data = NULL;
    struct neural_node *  learning_data = NULL;
    struct neural_node *  result_data = NULL;
    int NUM_ALL_LAYER = arg->hidden_layer + 2;
    int CURRENT_NUM_NODE,PREV_NUM_NODE;
    double e1,e2,tmp1,tmp2,temp_weight;

    input_data = data_list->next_layer->node;
    
    if(GET_DELTA == status){
        last_layer = neural->layer;
        while(NULL != last_layer->next_layer){
            last_layer = last_layer->next_layer;
        }  
    }
    
    for(i = 0;i < NUM_ALL_LAYER;i++){
        obj = obj->next_layer; 
        current_node = obj->node;
        CURRENT_NUM_NODE = arg->node_array[i];
        if(INPUT_LAYER != i)
            prev_layer_node = obj->prev_layer->node->next_node;
        for(j = 0;j < CURRENT_NUM_NODE;j++){
            current_node = current_node->next_node;
            if(FORECAST == status)||(INIT == status){
                current_node->out = 0;
            }
            if(INPUT_LAYER == i){
                if(INIT == status){
                    current_node->out = 0;
                }
                else if(FORECAST == status){
                    input_data = input_data->next_node;
                    current_node->out = input_data->out;
                }
            }
            else{            
                PREV_NUM_NODE = arg->node_array[i-1];
                for(k = 0; k < PREV_NUM_NODE;k++){
                    if(INIT == status){
                        current_node->weight[k] = rand_num(1);
                        current_node->delta_weight[k] = 0;
                    }
                    else if(FORECAST == status){
                        current_node->out += prev_layer_node->out * current_node->weight[k];
                        prev_layer_node = prev_layer_node->next_node;                        
                    }
                    else if(ADD_DELTA == status){
                        current_node->weight[k] = current_node->weight[k] + current_node->delta_weight[k];
                    }
                    else if(GET_DELTA == status){                        
                        e1 = 0;
                        e2 = 0;

                        learning_data = data_list->next_layer->next_layer->node;                    
                        result_data = last_layer->node;                    
                        neural->run(neural,data_list,FORECAST);
                        while(NULL != learning_data->next_node)&&(NULL != result_data->next_node){
                            learning_data = learning_data->next_node;
                            result_data = result_data->next_node;
                            tmp1 = (result_data->out - learning_data->out); 
                            e1 = e1 + (tmp1 * tmp1);    
                        }
                        e1 = e1 / 2.0;    

                        
                        temp_weight = current_node->weight[k];
                        current_node->weight[k] = current_node->weight[k] + POSITIVE_PARTIAL_DERIVATIVES_COEFFICIENT;


                        learning_data = data_list->next_layer->next_layer->node;                    
                        result_data = last_layer->node;
                        neural->run(neural,data_list,FORECAST);
                        while(NULL != learning_data->next_node)&&(NULL != result_data->next_node){
                            learning_data = learning_data->next_node;
                            result_data = result_data->next_node;
                            tmp1 = (result_data->out - learning_data->out); 
                            e2 = e2 + (tmp1 * tmp1);    
                        }
                        e2 = e2 / 2.0;    

                        
                        current_node->delta_weight[k] = LEARNING_RATE * (e1- e2) / POSITIVE_PARTIAL_DERIVATIVES_COEFFICIENT;
                        current_node->weight[k] = temp_weight;
                    }
                }
                if(FORECAST == status){
                    current_node->out = act_squashing_function(current_node->out);                                         
                }                
            }
        }
    }
    return 1;
}

struct neural_context * neural_context_alloc(void)
{
    struct neural_context * obj = kzalloc(sizeof(*obj),GFP_USER);
    LEARN_LOG("neural_context_alloc+++\n");
    if(!obj){
        LEARN_ERR("alloc neural context error! \n");
        return NULL;
    }
    rand_init();
    
    obj->arg =  get_arch_arg();
    obj->layer = layers_context_alloc(obj->arg);
    obj->run = neural_run;
  
    return obj;
}


int main()
{ 
    ne = neural_context_alloc();  
    ne->run(ne,NULL,INIT);
    ne->run(ne,NULL,GET_DELTA);
    ne->run(ne,NULL,ADD_DELTA);
    ne->run(ne,NULL,FORECAST);

    
	return 0;
}


 
