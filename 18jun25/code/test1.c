#include <stdio.h>
#define LORA_SEND_CMD(addr, len, msg)  "AT+SEND=" #addr "," #len "," msg "\r\n"

int main(){
	char str[]=LORA_SEND_CMD(1,2,"HI AMER");
	printf(str);
	return 0;
}
