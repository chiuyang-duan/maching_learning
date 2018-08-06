#include "Common.h"


/*
study aim:
    y<x && y>0 && x<5
input:
    data_x   
    data_y
aim in triangle:
    data_out1 = 0.9;
    data_out2 = -0.9;
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
           data_out[0][i] = 0.9;
           data_out[1][i] = -0.9;
        }
        else
        {
            data_out[0][i] = -0.9;
            data_out[1][i] = 0.9;
        }
    }    
}


void init_data(struct input_data * datain, struct output_data * dataout)
{
    datain = (input_data *)malloc(sizeof(input_data));
    dataout = (output_data *)malloc(sizeof(output_data));  
    memset(datain,0,sizeof(input_data));
    memset(dataout,0,sizeof(output_data));

    datain->input_num = INPUT_NUM;              //2;
    datain->out_num = OUT_NUM;                  //2;
    datain->hidden_layer_num = HIDDEN_LAYER_NUM;//4;

    datain->x = (double *)malloc((datain->input_num) * sizeof(double))
    memset(datain->x,0,(datain->input_num) * sizeof(double));

    dataout->hidden_b = (double *)malloc(datain->hidden_layer_num * sizeof(double));         
    dataout->para_v = (double *)malloc(((datain->input_num + 1) * datain->hidden_layer_num) * sizeof(double));
    dataout->para_w = (double *)malloc(datain->out_num * (datain->hidden_layer_num + 1) * sizeof(double));    
    dataout->y = (double *)malloc((datain->out_num) * sizeof(double)); 
    
    memset(dataout->hidden_b,0,datain->hidden_layer_num * sizeof(double));
    memset(dataout->para_v,0,((datain->input_num + 1) * datain->hidden_layer_num) * sizeof(double));
    memset(dataout->para_w,0,datain->out_num * (datain->hidden_layer_num + 1)*sizeof(double));    
    memset(dataout->y,0,(datain->out_num) * sizeof(double));
    
}

struct delta_parameters{

    double * w;
    double * theta;
    
    double * v;
    double * gama;
    
};
void init_delta_para(struct input_data * datain, struct delta_parameters * delta_para)
{
    delta_para = (delta_parameters *)malloc(sizeof(delta_parameters));
    delta_para->v = (double *)malloc(datain->input_num * datain->hidden_layer_num * sizeof(double)); 
    delta_para->theta = (double *)malloc(datain->hidden_layer_num * sizeof(double));
        
    delta_para->w = (double *)malloc(datain->out_num * datain->hidden_layer_num * sizeof(double)); 
    delta_para->gama = (double *)malloc(datain->out_num * sizeof(double));
    
    memset(datain,0,sizeof(input_data));    
    memset(delta_para->v,0,datain->input_num * datain->hidden_layer_num * sizeof(double)); 
    memset(delta_para->theta,0,sizeof(datain->hidden_layer_num * sizeof(double)));
    
    memset(delta_para->w,0,datain->out_num * datain->hidden_layer_num * sizeof(double));   
    memset(delta_para->gama,0,sizeof(datain->out_num * sizeof(double)));
}
void free_delta_para(struct input_data * datain, struct delta_parameters * delta_para)
{
    free(delta_para->v);
    free(delta_para->theta);
    
    free(delta_para->w);
    free(delta_para->gama);
    
    free(datain);    
}
void free_data(struct input_data * datain, struct output_data * dataout)
{
    free(dataout->hidden_b);
    free(dataout->para_w);
    free(dataout->para_v);
    free(dataout->y);  
    free(dataout);
    free(datain->x);
    free(datain);
}
/*
bp_function() is one hidden_layer function
*/
void bp_function(struct input_data * datain, struct output_data * dataout)
{
    int i,j;
    for(i = 0; i< datain->hidden_layer_num;i++)
    {
        for(j = 0;j < datain->input_num;j++)
        {
            dataout->hidden_b[i] = dataout->hidden_b[i] + datain->x[j] * dataout->para_v[(i * datain->input_num)+j];            
        } 
        dataout->hidden_b[i] = act_squashing_function(dataout->hidden_b[i] + (-1.0) * dataout->para_v[(i * datain->input_num)+j]);
    }
    for(i = 0; i< datain->out_num;i++)
    {
        for(j = 0;j < datain->hidden_layer_num;j++)
        {
            dataout->y[i] = dataout->y[i] + dataout->hidden_b[j] * dataout->para_w[(i * datain->hidden_layer_num)+j];            
        } 
        dataout->y[i] = act_squashing_function(dataout->y[i] + (-1.0) * dataout->para_w[(i * datain->hidden_layer_num)+j]); 
    }    
}
void para_iteration(struct input_data * datain, struct output_data * dataout, struct delta_parameters * delta_para)
{
    int i,j;

    for(i = 0; i< datain->hidden_layer_num;i++)
    {
        for(j = 0;j < datain->input_num;j++)
        {
            dataout->para_v[(i * datain->input_num)+j];      

            

            
        } 
    }
    for(i = 0; i< datain->out_num;i++)
    {
        for(j = 0;j < datain->hidden_layer_num;j++)
        {
            dataout->para_w[(i * datain->hidden_layer_num)+j];   



            
        } 
    }   

}

int main()
{
    double input_x[2];
    
    struct input_data * datain;
    struct output_data * dataout;
    struct delta_parameters * delta_para;

    init_data(datain, dataout);
    init_delta_para(datain,delta_para);
    
    for(j = 0; j < 1500; j++)
    {
        for(i = 0; i < max; i++)
        {
            datain->x[i] = data_x[i][j];         
        }         
        bp_function(datain, dataout);
        para_iteration(datain, dataout, delta_para);
    }
    




    
    printf("       |        .    .       '\n");
    printf("       |        .  .         '\n");
    printf("       |        ..           '\n");
    printf("       |       ..            '\n");
    printf("       |     .++.            '\n");
    printf("       |   .++++.            '\n");
    printf("       | .++++++.            '\n");
    printf("-------.--------.------------'\n");
    printf("     . |        .            '\n");
    printf("   .   |        .            '\n");
    printf(" .     |        .            '\n");
    
    
    printf("pls input test data 'input_x1,input_x2'\n");
    scanf("%lf,%lf",input_x[0],input_x[1]);


    free_delta_para(datain, delta_para)

    free_data(datain, dataout)
        
	return 0;
}



















 
