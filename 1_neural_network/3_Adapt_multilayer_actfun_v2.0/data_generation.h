#ifndef DATA_GENERATION_H_INCLUDED
#define DATA_GENERATION_H_INCLUDED
#include "Common.h"

#define GET_FORECAST_DATA 1

#define INPUT_NODE 2
#define OUTPUT_NODE 2
struct neural_context * input_data_context_alloc(void);
int get_input_data(struct neural_context * neural,struct neural_layer * data_list, int status);
struct neural_arg * set_input_data_arg();
int make_study_data1(struct neural_context * input_data);
void study_data1_result();
int run_get_input_data(struct neural_context * ,struct neural_context * , int );



#endif
