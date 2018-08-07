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

void rand_init()
{
    srand((int)time(0)); 
}
double rand_num(double max)
{
	double rand1;
	rand1 = (((double)(rand()%1000)/1000.0 * (2 * max)) - max);
    return rand1;
}

void make_study_data()
{

    int i;
    for(i = 0;i<1500;i++)
    {
        data_x[0][i] = rand_num(10);
        data_x[1][i] = rand_num(10);
        
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
	int i,j;
	
    datain = (struct input_data *)malloc(sizeof(struct input_data));
    dataout = (struct output_data *)malloc(sizeof(struct output_data));  
    memset(datain,0,sizeof(struct input_data));
    memset(dataout,0,sizeof(struct output_data));

    datain->input_num = INPUT_NUM;              //2;
    datain->out_num = OUT_NUM;                  //2;
    datain->hidden_layer_num = HIDDEN_LAYER_NUM;//4;

    datain->x = (double *)malloc((datain->input_num) * sizeof(double));
    datain->y = (double *)malloc((datain->out_num) * sizeof(double));
    memset(datain->y,0,(datain->out_num) * sizeof(double));
    memset(datain->x,0,(datain->input_num) * sizeof(double));

    dataout->hidden_b = (double *)malloc(datain->hidden_layer_num * sizeof(double));         
    dataout->para_v = (double *)malloc(((datain->input_num + 1) * datain->hidden_layer_num) * sizeof(double));
    dataout->para_w = (double *)malloc(datain->out_num * (datain->hidden_layer_num + 1) * sizeof(double));    
    dataout->y = (double *)malloc((datain->out_num) * sizeof(double)); 
    
    memset(dataout->hidden_b,0,datain->hidden_layer_num * sizeof(double));
    memset(dataout->para_v,0,((datain->input_num + 1) * datain->hidden_layer_num) * sizeof(double));
    memset(dataout->para_w,0,datain->out_num * (datain->hidden_layer_num + 1)*sizeof(double));    
    memset(dataout->y,0,(datain->out_num) * sizeof(double));


    for(i = 0; i< datain->hidden_layer_num; i++)
    {
        for(j = 0;j < datain->input_num; j++)
        {
            dataout->para_v[(i * (datain->input_num + 1)) + j] = rand_num(1);            
        } 
        dataout->para_v[(i * datain->input_num) + j] = rand_num(1);
    }
    for(i = 0; i< datain->out_num; i++)
    {
        for(j = 0;j < datain->hidden_layer_num; j++)
        {
            dataout->para_w[(i * (datain->hidden_layer_num + 1)) + j] = rand_num(1);            
        } 
        dataout->para_w[(i * datain->hidden_layer_num) + j] = rand_num(1); 
    }   
    
}

void init_delta_para(struct input_data * datain, struct delta_parameters * delta_para)
{
    delta_para = (struct delta_parameters *)malloc(sizeof(struct delta_parameters));

    delta_para->v = (double *)malloc(datain->input_num * datain->hidden_layer_num * sizeof(double)); 
    delta_para->theta = (double *)malloc(datain->hidden_layer_num * sizeof(double));
        
    delta_para->w = (double *)malloc(datain->out_num * datain->hidden_layer_num * sizeof(double)); 
    delta_para->gama = (double *)malloc(datain->out_num * sizeof(double));

    delta_para->gradient = (double *)malloc(datain->out_num * sizeof(double));  
    
    memset(delta_para->v,0,datain->input_num * datain->hidden_layer_num * sizeof(double)); 
    memset(delta_para->theta,0,sizeof(datain->hidden_layer_num * sizeof(double)));
    
    memset(delta_para->w,0,datain->out_num * datain->hidden_layer_num * sizeof(double));   
    memset(delta_para->gama,0,sizeof(datain->out_num * sizeof(double)));
    
    memset(delta_para->gradient,0,sizeof(datain->out_num * sizeof(double)));
}
void free_delta_para(struct delta_parameters * delta_para)
{
    free(delta_para->v);
    free(delta_para->theta);
    
    free(delta_para->w);
    free(delta_para->gama);

    free(delta_para->gradient); 
}
void free_data(struct input_data * datain, struct output_data * dataout)
{
    free(dataout->hidden_b);
    free(dataout->para_w);
    free(dataout->para_v);
    free(dataout->y);  
    free(dataout);
    free(datain->x);
    free(datain->y);
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
            dataout->hidden_b[i] = dataout->hidden_b[i] + datain->x[j] * dataout->para_v[(i * (datain->input_num + 1))+j];            
        } 
        dataout->hidden_b[i] = act_squashing_function(dataout->hidden_b[i] + (-1.0) * dataout->para_v[(i * datain->input_num)+j]);
    }
    for(i = 0; i< datain->out_num;i++)
    {
        for(j = 0;j < datain->hidden_layer_num;j++)
        {
            dataout->y[i] = dataout->y[i] + dataout->hidden_b[j] * dataout->para_w[(i * (datain->hidden_layer_num + 1))+j];            
        } 
        dataout->y[i] = act_squashing_function(dataout->y[i] + (-1.0) * dataout->para_w[(i * datain->hidden_layer_num)+j]); 
    }    
}
void para_iteration(struct input_data * datain, struct output_data * dataout, struct delta_parameters * delta_para, double learning_rate)
{
    int i,j,k;
    double sum_w_g = 0;
	double eh = 0;
    for(i = 0; i < datain->out_num;i++)
    {
    	delta_para->gradient[i] = dataout->y[i] * (1 - dataout->y[i]) * (datain->y[i] - dataout->y[i]);
        for(j = 0;j < datain->hidden_layer_num;j++)
        {
            delta_para->w[(i * datain->hidden_layer_num)+j] = learning_rate * delta_para->gradient[i] * dataout->hidden_b[j];            
        } 
        delta_para->theta[i] = (-1) * learning_rate * delta_para->gradient[i];
    }
    
    for(i = 0; i < datain->hidden_layer_num;i++)
    {  
        for(k = 0; k < datain->out_num; k++)
        {
            sum_w_g = sum_w_g + (delta_para->gradient[k] * dataout->para_w[k * datain->hidden_layer_num + i]);             
        }
        eh = dataout->hidden_b[i] * (1 - dataout->hidden_b[i]) * sum_w_g;
        for(j = 0;j < datain->input_num;j++)
        {                
            delta_para->v[i * datain->input_num + j] = learning_rate * eh * datain->x[j];
        } 
        delta_para->gama[i] = (-1) * learning_rate * eh;
    }


    for(i = 0; i< datain->hidden_layer_num;i++)
    {
        for(j = 0;j < datain->input_num;j++)
        {
             dataout->para_v[(i * (datain->input_num + 1)) + j] = dataout->para_v[(i * (datain->input_num + 1)) + j] + delta_para->v[(i * datain->input_num) + j];            
        } 
        dataout->para_v[(i * datain->input_num) + j] = dataout->para_v[(i * datain->input_num) + j] + delta_para->gama[i];
    }
    for(i = 0; i< datain->out_num;i++)
    {
        for(j = 0;j < datain->hidden_layer_num;j++)
        {
            dataout->para_w[(i * (datain->hidden_layer_num + 1)) + j] = dataout->para_w[(i * (datain->hidden_layer_num + 1)) + j] + delta_para->w[(i * datain->hidden_layer_num) +j];            
        } 
        dataout->para_w[(i * datain->hidden_layer_num)+j] = dataout->para_w[(i * datain->hidden_layer_num)+j] + delta_para->theta[i]; 
    }    
}

int main()
{
	int i,j;
	
	double input_x[2];
    
    struct input_data * datain = NULL;
    struct output_data * dataout = NULL;
    struct delta_parameters * delta_para = NULL;
	double learning_rate = 0;
	
    rand_init();
    init_data(datain, dataout);
    init_delta_para(datain,delta_para);
    make_study_data();
	
	printf("pls input learning rate\n");
	scanf("%lf",&learning_rate);
	
    for(j = 0; j < 1500; j++)
    {
        for(i = 0; i < 2; i++)
        {
            datain->x[i] = data_x[i][j];  
			datain->y[i] = data_out[i][j];
        }         
        bp_function(datain, dataout);
        para_iteration(datain, dataout, delta_para, learning_rate);
    }

	printf("learning success\n");
    while(1)
    {
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
        scanf("%lf,%lf",&input_x[0],&input_x[1]);

        datain->x[0] = input_x[0];
        datain->x[1] = input_x[1];
        bp_function(datain, dataout);
        printf("%lf,%lf\n",dataout->y[0],dataout->y[1]);
        
    }

    free_delta_para(delta_para);
    free_data(datain, dataout);
        
	return 0;
}



















 
