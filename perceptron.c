#include <stdio.h>
#define DEBUG 0
#if DEBUG
#define LEARNING_LOG(...) printf("Filename %s, Function %s, Line %d > ", __FILE__, __FUNCTION__, __LINE__); \
                            printf(__VA_ARGS__); \
                            printf("\n");
#else
#define LEARNING_LOG(...)
#endif

#define LEARNING_RATE 0.4

float sigmod_function(float x);
float sum_node(float w1,float w2,float theta, float x1,float x2);
void study(float *w1,float *w2,float *theta,float input_x1,float input_x2,float input_y,float learning_rate);


struct neuron
{
    float (*sgn)(float x);
    float (*functional_neuron)(float w1,float w2,float theta, float x1,float x2);
    void (*study_neuron)(float *w1,float *w2,float *theta,float input_x1,float input_x2,float input_y,float learning_rate);
};

struct neuron perceptron = {
    .sgn                =   sigmod_function,
    .functional_neuron  =   sum_node,
    .study_neuron       =   study,
};

float sigmod_function(float x)
{
    if(0 <= x)
        return 1;
    else
        return 0;
}

float sum_node(float w1,float w2,float theta, float x1,float x2)
{
    LEARNING_LOG("w1(%f) * x1(%f) + \n w2(%f) * x2(%f) - \ntheta(%f)\n", w1,x1,w2,x2,theta);
    return (w1 * x1 + w2 * x2 + ((-1) * theta));
}

void study(float *w1,float *w2,float *theta,float input_x1,float input_x2,float input_y,float learning_rate)
{
    float out_y;
    out_y = learning_rate * (input_y - sigmod_function(sum_node(*w1,*w2,*theta,input_x1,input_x2)));
    *w1 = out_y * input_x1 + *w1;
    *w2 =  out_y * input_x2 + *w2;
    *theta = (-1.0) * out_y + *theta;
}

float test_data[4][3] = 
{{1,1,1},
{1,0,1},
{0,1,1},
{0,0,0},
};

int main()
{
    float w1 = 0.1;
    float w2 = 0.2;
    float theta = 0.3;
    float x1 = 0;
    float x2 = 0;
    int i;
    float learning_rate;
    printf("please input learning_rate\n");
    scanf("%f",&learning_rate);
    for(i = 0;i < 4; i++)
    {
        study(&w1,&w2,&theta, test_data[i][0],test_data[i][1],test_data[i][2],learning_rate);
        LEARNING_LOG("\n\n w1(%f) w2(%f)\n", w1,w2);
    }
    LEARNING_LOG("w1(%f) w2(%f)\n", w1,w2);
    while(1)
    {
        printf("please input 'x1,x2'\n");
        scanf("%f,%f",&x1,&x2);
        LEARNING_LOG("x1 = %f,x2 = %f \n",x1,x2);
        if(sigmod_function(sum_node(w1,w2,theta,x1,x2)))
        {
            printf("out 1\n"); 
        }        
        else 
        {
            printf("out 0\n");
        }
    }
    return 0;
}















