#include "Common.h"


#define DEBUG 1
#if DEBUG
#define LEARNING_LOG(...) printf("Filename %s, Function %s, Line %d > ", __FILE__, __FUNCTION__, __LINE__); \
                          printf(__VA_ARGS__); \
                          printf("\n");
#else
#define LEARNING_LOG(...)
#endif

void get_arch_arg(struct * neural_arch)
{
    int i;
    
    printf("pls input num input_node_num:");
    scanf("%d",&neural_arch->input_node_num);
    printf("\npls input num output_node_num:");
    scanf("%d",&neural_arch->output_node_num);
    printf("\npls input num hidden_layer_num:");
    scanf("%d",&neural_arch->hidden_layer_num);
    
    if(NULL == (neural_arch->hidden_layer_node_num = (int *)malloc(neural_arch->hidden_layer_num * sizeof(int)))){
        LEARNING_LOG("malloc error \n");
    }
    memset(neural_arch->hidden_layer_node_num,0,neural_arch->hidden_layer_num * sizeof(int));

    for(i = 0; i < neural_arch->hidden_layer_num; i++)
    {
        printf("\npls input %d_layer_node_num:",i+1);
        scanf("%d",&neural_arch->hidden_layer_node_num[i]);
    }
    
}
struct neural_arch cust_neral_arch{

    .get_arg = get_arch_arg;
};

int main()
{
    get_arch_arg();
    
	return 0;
}


 
