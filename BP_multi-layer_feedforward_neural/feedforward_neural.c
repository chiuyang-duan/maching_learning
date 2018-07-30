#include "Common.h"
#include <stdlib.h>
#include <time.h>

/*学习目标 
y<x && y>0 && x<5
输入 
data_x   
data_y
目标在函数的三角形区域里边
data_out1 = 1;
data_out2 = 0;
*/
double data_x[2][1500];
double data_out[2][1500]; 

void make_study_data()
{

    int i;
    srand((int)time(0));
    for(i = 0;i<1500;i++)
    {
        data_x[0][i] = (rand()/double(RAND_MAX)*20)-10;
        data_x[1][i] = (rand()/double(RAND_MAX)*20)-10;
        
        if((data_x[1][i] < data_x[0][i])&&(data_x[1][i] > 0)&&(data_x[0][i] < 5))
        {
           data_out[0][i] = 1;
           data_out[1][i] = 0;
        }
        else
        {
            data_out[0][i] = 3;
            data_out[1][i] = 4;
        }       
    }    
}
/*
bp_function() is one hidden_layer function
*/

void bp_function(double *input_data)
{
    int input_num = 2; //none dummy node
    int out_num = 2;   //none dummy node
    int hidden_layer_num = 4;  //none dummy node
    double * para_w;
    double * para_v;
    int i,j;
    double * hidden_b;
    double * out_data;
    hidden_b = (double *)malloc(hidden_layer_num*sizeof(double)); 
    para_w = (double *)malloc(out_num*(hidden_layer_num+1)*sizeof(double)); 
    para_v = (double *)malloc(((input_num + 1)*hidden_layer_num)*sizeof(double)); 
    out_data = (double *)malloc((out_num)*sizeof(double)); 
    
    for(i = 0; i< hidden_layer_num;i++)
    {
        for(j = 0;j < input_num;j++)
        {
            hidden_b[i] = hidden_b[i] + input_data[j]* para_v[(i*input_num)+j];            
        } 
        hidden_b[i] = hidden_b[i] - para_v[(i*input_num)+j];
    }
    
    for(i = 0; i< out_num;i++)
    {
        for(j = 0;j < hidden_layer_num;j++)
        {
            out_data[i] = out_data[i] + hidden_b[j]* para_w[(i*hidden_layer_num)+j];            
        } 
        out_data[i] = out_data[i] - para_w[(i*hidden_layer_num)+j]; 
    }    
    
    free(out_data);
    free(para_w);
    free(para_v);
    free(hidden_b);    
}
int main()
{
    double input_x[2];
    printf("pls input test data 'input_x1,input_x2'\n");
    scanf("%lf,%lf",input_x[0],input_x[1]);


    
	return 0;
}



















 
