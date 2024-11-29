#include <LPC21XX.h>
#define FOSC 12000000
#define CCLK 5*FOSC
#define PCLK CCLK/4
#define BAUD 9600
#define DIVISOR (PCLK/(16*BAUD))
//uart defines
#define TX 1<<0
#define RX 1<<2
#define DLAB 1<<7
//u0lsr
#define THER 5
#define RDR 0
#define TEMT 6
char ch,dummy;


void UART0(){
PINSEL0|=0x00000005;
U0LCR=0x83;
U0DLL=DIVISOR&0xff;
U0DLM=DIVISOR>>8;
U0LCR=0x03;
}
void uart_tx(char ch)
{
	U0THR=ch;
	while(((U0LSR>>TEMT)&1)==0);
}
char uart_rx()
{
while(((U0LSR>>RDR)&1)==0);
return U0RBR;
}
void UART_isr(void) __irq
{
	if((U0IIR&0x04))
	{
		char r;
		r=uart_rx();
		uart_tx(r);
		uart_tx('\r');
		uart_tx('\n');
		dummy=U0IIR;
		
	}
	else{
		//uart_tx('b');
		dummy=U0IIR;
	}
	VICVectAddr=0;
}
void uart_int(){
	VICIntSelect=0x00;
	VICVectCntl0=0x20|6;
	VICVectAddr0=(unsigned)UART_isr;
	VICIntEnable=1<<6;
	U0IER=0x03;
}
int main()
{
	UART0();
	uart_int();
while(1){
	int i;
	uart_tx('a');
	for(i=1000000;i>=0;i--);
	uart_tx('\r');
	uart_tx('\n');
}
}
