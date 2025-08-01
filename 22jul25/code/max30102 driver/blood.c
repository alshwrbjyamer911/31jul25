/**
 * ************************************************************************
 *
 * @file blood.c
 * @author zxr
 * @brief
 *
 * ************************************************************************
 * @copyright Copyright (c) 2024 zxr
 * ************************************************************************
 */
#include "blood.h"
#include "usart.h"

int heart;
float SpO2;


extern uint16_t fifo_red;
extern uint16_t fifo_ir;

uint16_t g_fft_index = 0;
struct compx s1[FFT_N+16];
struct compx s2[FFT_N+16];



#define CORRECTED_VALUE			47

/**
 * ************************************************************************
 * @brief
 * @note
 * ************************************************************************
 */
void blood_data_update(void)
{

	g_fft_index=0;
	while(g_fft_index < FFT_N)
	{
		while(max30102_read_reg(REG_INTR_STATUS_1)&0x40 )
		{

			max30102_read_fifo();  //read from MAX30102 FIFO2

			if(g_fft_index < FFT_N)
			{

				s1[g_fft_index].real = fifo_red;
				s1[g_fft_index].imag= 0;
				s2[g_fft_index].real = fifo_ir;
				s2[g_fft_index].imag= 0;
				g_fft_index++;
			}
		}
	}
}


/**
 * ************************************************************************
 * @brief
 *
 *
 * ************************************************************************
 */
void blood_data_translate(void)
{
	float n_denom;
	uint16_t i;


	float dc_red =0;
	float dc_ir =0;
	float ac_red =0;
	float ac_ir =0;

	for (i=0 ; i<FFT_N ; i++ )
	{
		dc_red += s1[i].real ;
		dc_ir +=  s2[i].real ;
	}
		dc_red =dc_red/FFT_N ;
		dc_ir =dc_ir/FFT_N ;
	for (i=0 ; i<FFT_N ; i++ )
	{
		s1[i].real =  s1[i].real - dc_red ;
		s2[i].real =  s2[i].real - dc_ir ;
	}


	for(i = 1;i < FFT_N-1;i++)
	{
		n_denom= ( s1[i-1].real + 2*s1[i].real + s1[i+1].real);
		s1[i].real=  n_denom/4.00;

		n_denom= ( s2[i-1].real + 2*s2[i].real + s2[i+1].real);
		s2[i].real=  n_denom/4.00;
	}


	for(i = 0;i < FFT_N-8;i++)
	{
		n_denom= ( s1[i].real+s1[i+1].real+ s1[i+2].real+ s1[i+3].real+ s1[i+4].real+ s1[i+5].real+ s1[i+6].real+ s1[i+7].real);
		s1[i].real=  n_denom/8.00;

		n_denom= ( s2[i].real+s2[i+1].real+ s2[i+2].real+ s2[i+3].real+ s2[i+4].real+ s2[i+5].real+ s2[i+6].real+ s2[i+7].real);
		s2[i].real=  n_denom/8.00;

	}


	g_fft_index = 0;

	FFT(s1);
	FFT(s2);

	for(i = 0;i < FFT_N;i++)
	{
		s1[i].real=sqrtf(s1[i].real*s1[i].real+s1[i].imag*s1[i].imag);
		s1[i].real=sqrtf(s2[i].real*s2[i].real+s2[i].imag*s2[i].imag);
	}

	for (i=1 ; i<FFT_N ; i++ )
	{
		ac_red += s1[i].real ;
		ac_ir +=  s2[i].real ;
	}

	for(i = 0;i < 50;i++)
	{
		if(s1[i].real<=10)
			break;
	}


	int s1_max_index = find_max_num_index(s1, 60);
	int s2_max_index = find_max_num_index(s2, 60);


	if(i>=45)
	{

		uint16_t Heart_Rate = 60.00 * SAMPLES_PER_SECOND * s1_max_index / FFT_N;
		heart = Heart_Rate;


		float R = (ac_ir*dc_red)/(ac_red*dc_ir);
		float sp02_num = -45.060*R*R+ 30.354 *R + 94.845;
		SpO2 = sp02_num;


	}
	else
	{
		heart = 0;
		SpO2 = 0;
	}

}

/**
 * ************************************************************************
 * @brief
 *
 *
 * ************************************************************************
 */
void blood_Loop(void)
{

	blood_data_update();

	blood_data_translate();

	SpO2 = (SpO2 > 99.99) ? 99.99:SpO2;

	printf("pulse-rate%3d/min; oximetry%2d%%\n", heart, (int)SpO2);

}

