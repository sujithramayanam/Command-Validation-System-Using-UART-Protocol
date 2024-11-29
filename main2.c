#include <LPC21xx.H>  /* LPC21xx definitions         */
#include <string.h>

#include "delay.h"
#include "uart.h"
#include "uart_defines.h"

extern char buff[50],err[100]="ERROR!!TRY AGAIN",res[100]="";
extern unsigned char i,r_flag,t_flag;
unsigned int cnt=0,v=0;
int is_it_true(char *s){
if(s[2]=='8'&&s[3]=='6'&&s[4]=='7'&&s[5]=='5'&&s[6]=='#')
	return 1;
else
	return 0;
}
void result(char *s){
cnt=0,v=0;
while(*s++){
if(*s=='#')
	cnt++;
if(cnt==2){
	res[v]=*s;
	v++;
}
}
}							
int main()
{

  InitUART0();
	while(1){
	UART0_Str("enter command");
	UART0_Str("\r\n");
	UART0t_Str(buff);
	if((buff[0]=='@')&&(buff[1]=='#')&&(buff[strlen(buff)-1]=='$')&&is_it_true(buff)){
		result(buff);
		res[strlen(res)-1]='\0';
		UART0_Str("!!valid command!!\r\n");
	UART0_Str(res+1);}
	else{
		UART0_Str("!!invalid command!!\r\n");
		UART0_Str(err);
	}
	UART0_Str("\r\n");
	
	
	}
	
}
