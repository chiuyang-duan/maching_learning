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

double data_x[2][TEST_NUM];
double data_out[2][TEST_NUM]; 

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


void study_data1_result()
{
    printf("                             \n");
    printf("       |        .    .       \n");
    printf("       |        .  .         \n");
    printf("       5      (5,5)          \n");
    printf("       |       ..            \n");
    printf("       |     .++.            \n");
    printf("       |   .++++.            \n");
    printf("       | .++++++.            \n");
    printf("-------0--------5------------\n");
    printf("     . |        .            \n");
    printf("   .   |        .            \n");
    printf(" .     |        .            \n");    
    printf("          study aim:         \n");
    printf("       y<x && y>0 && x<5.    \n");       
}

void make_study_data1()
{

    int i;
    LEARN_LOG("make_study_data1\n");
    printf("       y<x && y>0 && x<5.    \n"); 
    for(i = 0;i<TEST_NUM;i++)
    {
        data_x[0][i] = rand_num(10);
        data_x[1][i] = rand_num(10);
        
        if((data_x[1][i] < data_x[0][i])&&(data_x[1][i] > 0)&&(data_x[0][i] < 5))
        {
           data_out[0][i] = 0.9;
           data_out[1][i] = 0.01;
        }
        else
        {
            data_out[0][i] = 0.01;
            data_out[1][i] = 0.9;
        }
    }    
}
void study_data2_result()
{
    printf("                 . ++++++++++\n");
    printf("       |       . ++++++++++++\n");
    printf("       |     . ++++++++++++ .\n");
    printf("       5   . ++++++++++++ .  \n");
    printf("       | . ++++++++++++ .    \n");
    printf("       3 ++++++++++++ .      \n");
    printf("     . |+++++++++++ .        \n");
    printf("   . ++|+++++++++ .          \n");
    printf("-------0--------5------------\n");
    printf(". +++++|+++++ .              \n");
    printf(" ++++++|+++ .                \n");
    printf(" ++++++|+ .                  \n");    
    printf("          study aim:         \n");
    printf("       y<x && y>0 && x<5.    \n");       
}

void make_study_data2()
{

    int i;
    LEARN_LOG("make_study_data1\n");
    printf("y < (x + 3) && y > (x-5)");
    for(i = 0;i<TEST_NUM;i++)
    {
        data_x[0][i] = rand_num(10);
        data_x[1][i] = rand_num(10);
        
        if((data_x[1][i] < (data_x[0][i] + 3))&&(data_x[1][i] > (data_x[0][i] - 5)))
        {
            data_out[0][i] = 0.9;
            data_out[1][i] = 0.01;
        }
        else
        {
            data_out[0][i] = 0.01;
            data_out[1][i] = 0.9;
        }
    }    
}

