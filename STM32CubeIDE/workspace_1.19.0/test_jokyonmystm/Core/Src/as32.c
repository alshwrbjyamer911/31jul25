#include "as32.h"


uint8_t lora_init(){
	//	0xC6 + 16byte Configure key
	//  Data encryption

	HAL_UART_Transmit(&huart2, enc_key, 17, 10);
	uint8_t transmition_status[5];
	HAL_UART_Receive(&huart2,transmition_status , 5, 100);
	if(transmition_status[0]=='O'){
		memset(transmition_status,0,5);
		return 0;//0 meaning ok its done
	}
	else{

		memset(transmition_status,5,0);
		return 1;//1 mean error the transmition is
	}
}

void lora_config(uint8_t config){
	//	MD0	Input (weak pull-up)	Works with MD1 to select one of four operation modes.
	//	2	MD1	Input (weak pull-up)	Works with MD0 to select one of four operation modes.
//	HAL_UART_Transmit(&huart2, pData, Size, Timeout)
}
uint8_t lora_send_data(uint8_t *data, uint8_t len){

	uint8_t transmition_status[5];
	HAL_UART_Transmit(&huart2, data, sizeof(data), 100);
	HAL_UART_Receive(&huart2,transmition_status , 5, 100);
	if(transmition_status[0]=='O'){
		memset(transmition_status,0,5);
		return 0;//0 meaning ok its done
	}
	else{

		memset(transmition_status,5,0);
		return 1;//1 mean error the transmition is
	}

}
uint8_t lora_recive(){

}
uint8_t checkerr(){

	uint8_t transmition_status[5];
	HAL_UART_Receive(&huart2,transmition_status , 5, 100);
	if(transmition_status[0]=='O'){
		memset(transmition_status,0,5);
		return 0;//0 meaning ok its done
	}
	else{

		memset(transmition_status,5,0);
		return 1;//1 mean error the transmition is
	}
}
