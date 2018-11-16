#include "Common.h"
#include "data_generation.h"

struct neural_context *ne;
struct neural_context *input_data;


int neural_run(struct neural_context * neural,struct neural_context * data_list, int status)
{
    int prev_num;
    int i,j,k;
    struct neural_layer * obj = neural->layer;
    struct neural_layer * layer_head = neural->layer;
    struct neural_layer * last_layer = NULL;
    struct neural_node * prev_layer_node = NULL;
    struct neural_node * temp_prev_layer_node = NULL;
    struct neural_node * current_node = NULL;
    struct neural_arg * arg = neural->arg;
    
    struct neural_node *  input_data = NULL;
    struct neural_node *  learning_data = NULL;
    struct neural_node *  result_data = NULL;
    int NUM_ALL_LAYER = arg->hidden_layer + 2;
    int CURRENT_NUM_NODE,PREV_NUM_NODE;
    double e1,e2,tmp1,tmp2,temp_weight;

    if(NULL != data_list){
        DEPOINT_LOG("input_data = data_list->layer->next_layer->node\n");
        input_data = data_list->layer->next_layer->node;
    }
    if(NULL != neural){
        last_layer = get_last_layer(neural);
    }
    
    for(i = 0;i < NUM_ALL_LAYER;i++){
        LEARN_LOG("layer i: %d status: %d\n",i,status);
        LEARN_LOG("obj = obj->next_layer;\n");
        obj = obj->next_layer; 
        DEPOINT_LOG("current_node = obj->node;\n");
        current_node = obj->node;
        CURRENT_NUM_NODE = arg->node_array[i];
        if(INPUT_LAYER != i)
        {
            DEPOINT_LOG("prev_layer_node = obj->prev_layer->node->next_node;\n");
            prev_layer_node = obj->prev_layer->node->next_node;
            temp_prev_layer_node = prev_layer_node;
        }
        for(j = 0;j < CURRENT_NUM_NODE;j++){
            LEARN_LOG("(j = 0;j < CURRENT_NUM_NODE = %d;j++){\n",CURRENT_NUM_NODE);
            LEARN_LOG("node j: %d status: %d\n",j,status);
            DEPOINT_LOG("current_node = current_node->next_node;\n");
            temp_prev_layer_node = prev_layer_node;
            current_node = current_node->next_node;
            
            if((FORECAST == status)||(INIT == status)){
                current_node->out = 0.0;
            }
            if(INPUT_LAYER == i){
                if(INIT == status){
                    current_node->out = DUMMY;
                }
                else if(FORECAST == status){
                    DEPOINT_LOG("input_data = input_data->next_node;\n");
                    input_data = input_data->next_node;
                    current_node->out = input_data->out;   
                    LEARN_LOG("current_node->out = %lf\n",current_node->out);
                }
            }
            else{
                prev_num = i-1;
                PREV_NUM_NODE = arg->node_array[prev_num];
                LEARN_LOG("(k = 0; k < PREV_NUM_NODE = %d ;k++)\n",PREV_NUM_NODE);
                for(k = 0; k < PREV_NUM_NODE;k++){
                    LEARN_LOG("prev num node weight k: %d status: %d\n",k,status);
                    if(INIT == status){
                        current_node->weight[k] = rand_num(1.0);                        
                        DATA_LOG("current_node->weight[%d]=%lf \n",k,current_node->weight[k]);                    
                        current_node->delta_weight[k] = 0.0;
                    }
                    else if(FORECAST == status){
                        if(((CURRENT_NUM_NODE - 1) == j) && ((NUM_ALL_LAYER - 1) != i)){
                            current_node->out = DUMMY;
                            LEARN_LOG("current_node->out = %lf\n",current_node->out);
                        }
                        else{                        
                            if((PREV_NUM_NODE - 1) == k){
                                LEARN_LOG("out %lf += -1 * weight[%d] %lf;\n",current_node->out,k,current_node->weight[k]);
                                current_node->out += DUMMY * current_node->weight[k];
                                LEARN_LOG("%d,%d current_node->out = %lf\n",i,j,current_node->out);
                            }
                            else{
                                LEARN_LOG("out %lf += prev->out %lf * weight[%d] %lf;\n",current_node->out,temp_prev_layer_node->out,k,current_node->weight[k]);
                                current_node->out += temp_prev_layer_node->out * current_node->weight[k];
                                LEARN_LOG("out = %lf \n",current_node->out);
                                DEPOINT_LOG("prev_layer_node = prev_layer_node->next_node;\n");
                                temp_prev_layer_node = temp_prev_layer_node->next_node;
                            }
                        }
                    }
                    else if(ADD_DELTA == status){
                        current_node->weight[k] = current_node->weight[k] + current_node->delta_weight[k];
                    }
                    else if(GET_DELTA == status){                        
                        e1 = 0;
                        e2 = 0;
                        DEPOINT_LOG("learning_data = data_list->layer->next_layer->next_layer->node;\n");
                        learning_data = data_list->layer->next_layer->next_layer->node;                    
                        result_data = last_layer->node; 
                        LEARN_LOG("\n\n 1 neural->run(neural,data_list,FORECAST);\n\n");
                        neural->run(neural,data_list,FORECAST);
                        
                        while((NULL != learning_data->next_node)&&(NULL != result_data->next_node)){
                            learning_data = learning_data->next_node;
                            result_data = result_data->next_node;
                            tmp1 = (result_data->out - learning_data->out); 
                            e1 = e1 + (tmp1 * tmp1);    
                        }
                        //e1 = e1 / 2.0;
                        e1 = e1 / ((double)(neural->arg->output_node));
                        //printf("E1 = %lf ,((double)(neural->arg->output_node))%d \n",e1,neural->arg->output_node);
                        
                        temp_weight = current_node->weight[k];
                        current_node->weight[k] = current_node->weight[k] + POSITIVE_PARTIAL_DERIVATIVES_COEFFICIENT;

                        learning_data = data_list->layer->next_layer->next_layer->node;                    
                        result_data = last_layer->node;
                        LEARN_LOG("2 neural->run(neural,data_list,FORECAST);\n");
                        neural->run(neural,data_list,FORECAST);
                        while((NULL != learning_data->next_node)&&(NULL != result_data->next_node)){
                            learning_data = learning_data->next_node;
                            result_data = result_data->next_node;
                            tmp1 = (result_data->out - learning_data->out); 
                            e2 = e2 + (tmp1 * tmp1);    
                        }
                        //e2 = e2 / 2.0;
                        e2 = e2 / ((double)(neural->arg->output_node));   
                        //printf("E2 = %lf \n",e2);
                        
                        current_node->delta_weight[k] = LEARNING_RATE * (e1 - e2) / POSITIVE_PARTIAL_DERIVATIVES_COEFFICIENT;
                        current_node->weight[k] = temp_weight;
                    }
                }
                if(FORECAST == status){                   
                    current_node->out = act_squashing_function(current_node->out);  
                    LEARN_LOG("%d,%d act_squ_fun(cur->out) = %lf\n",i,j,current_node->out);
                    LEARN_LOG("--------------------------------------------------\n\n");
                }                
            }
        }
    }
    return 1;
}

struct neural_context obj_ne = {
    .run = neural_run,
    .result_print = neural_result_print,
};

struct neural_context obj_input_data = {
    .run = run_get_input_data,
    .result_print =NULL,
};

struct neural_context * neural_context_alloc(void)
{
    obj_ne.arg =  get_arch_arg();
    obj_ne.layer = layers_context_alloc(obj_ne.arg);
    return &obj_ne;
}
struct neural_context * input_data_context_alloc(void)
{
    obj_input_data.arg = set_input_data_arg();
    obj_input_data.layer = layers_context_alloc(obj_input_data.arg);
    return &obj_input_data;
}


int main()
{ 
    int i;
 /*   
    struct neural_arg test_arg;
    struct neural_context test_data;
    test_data.arg = &test_arg;
    test_data.arg.input_node = -10;
    */
    
    rand_init();
    
    ne = neural_context_alloc();  
    input_data = input_data_context_alloc();
    LEARN_LOG("\n\nne->run(ne,NULL,INIT);\n\n");
    ne->run(ne,NULL,INIT);


    for(i = 0; i < LEARNING_NUM; i++){
        make_study_data1(input_data);
        LEARN_LOG("\n\nne->run(ne,input_data,GET_DELTA);\n\n");
        ne->run(ne,input_data,GET_DELTA);
        LEARN_LOG("\n\nne->run(ne,NULL,ADD_DELTA);\n\n");
        ne->run(ne,NULL,ADD_DELTA);
        printf("%d / %d \n",i,LEARNING_NUM);
    }
#if PRINT_TEST_DATA
    for(i = 0;i < 400;i++){       
        input_data->run(input_data,NULL,TEST_DATA);
        ne->run(ne,input_data,FORECAST);
        ne->result_print(ne);
        //printf("%d ",i);
    }
#endif
    while(1){
        input_data->run(input_data,NULL,GET_FORECAST_DATA);
        ne->run(ne,input_data,FORECAST);
        ne->result_print(ne);
    }
   
	return 0;
}


 
