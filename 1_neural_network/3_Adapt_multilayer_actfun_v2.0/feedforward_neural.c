#include "Common.h"


struct neural_context * ne = NULL;


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
    
    obj->arg =  get_arch_arg();
    obj->layer = layers_context_alloc(obj->arg);
    obj->run = neural_run;
  
    return obj;
}


int main()
{ 
    rand_init();

    ne = neural_context_alloc();  
    input_data = input_data_context_alloc();
    
    ne->run(ne,NULL,INIT);

    
    ne->run(ne,input_data,GET_DELTA);
    ne->run(ne,NULL,ADD_DELTA);

    
    ne->run(ne,input_data,FORECAST);

    
	return 0;
}


 
