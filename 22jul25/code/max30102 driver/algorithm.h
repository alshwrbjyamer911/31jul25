/**
 * ************************************************************************
 *
 * @file algorithm.h
 * @author zxr
 * @brief
 *
 * ************************************************************************
 * @copyright Copyright (c) 2024 zxr
 * ************************************************************************
 */
#ifndef __ALGORITHM_H
#define __ALGORITHM_H

#define FFT_N 			1024
#define START_INDEX 	8

struct compx
{
	float real;
	float imag;
};

typedef struct
{
	float w;
	int init;
	float a;
}DC_FilterData;


typedef struct
{
	float v0;
	float v1;
}BW_FilterData;



double my_floor(double x);

double my_fmod(double x, double y);

double XSin( double x );

double XCos( double x );

int qsqrt(int a);


struct compx EE(struct compx a,struct compx b);

void FFT(struct compx *xin);

int find_max_num_index(struct compx *data,int count);
int dc_filter(int input,DC_FilterData * df);
int bw_filter(int input,BW_FilterData * bw);


#endif
