#include <LPC21xx.H>  /* LPC21xx definitions         */
#include <string.h>

#include "delay.h"
#include "uart_defines.h"  

char buff[50]="hello",dummy;
unsigned char i=0,ch,r_flag,t_flag,ch1;
unsigned int y;

void UART0_isr(void) __irq
{
  if((U0IIR & 0x04)) //check if receive interrupt
  {
		ch = U0RBR;	/* Read to Clear Receive Interrupt */
		if(ch != 0x0d)//string termination "hit enter from keyboard"
			buff[i++] = ch; 
		else
		{
			buff[i] = '\0';
			i=0;
			r_flag = 1;
		}
  }
  else
  {
      dummy=U0IIR; //Read to Clear transmit interrupt
  }
   VICVectAddr = 0; /* dummy write */
}

void InitUART0 (void) /* Initialize Serial Interface       */ 
{  
	//cfg P0.0 as TXD0 & P0.1 as RXD0  functions
	PINSEL0 |= TXD0_EN|RXD0_EN;
	//cfg for 8data bits,1 stop bit,DLAB enabled 
	U0LCR=0x83;
	//Load Val for 9600 
	U0DLL=DIVISOR&0xff;
	U0DLM=DIVISOR>>8;
	//DLAB disabled
	U0LCR&=~(1<<DLAB_BIT); 
  
  #if UART_INT_ENABLE > 0

  VICIntSelect = 0x00000000; // IRQ 
  VICVectCntl0 = 0x20 | 6; // UART0 Interrupt 
	VICVectAddr0 = (unsigned)UART0_isr;
  VICIntEnable = 1 << 6;   // Enable UART0 Interrupt 
 
  U0IER = 0x03;       /* Enable UART0 RX and THRE Interrupts */ 
             
  #endif
						
}

void UART0_Tx(char ch)  /* Write character to Serial Port    */  
{ 
	U0THR=ch;
	while(((U0LSR>>TEMT_BIT)&1)==0);
                
}

char UART0_Rx(void)    /* Read character from Serial Port   */
{                     
  while(((U0LSR>>RDR_BIT)&1)==0);
	return U0RBR;
}

void UART0_Str(char *s)
{
   while(*s)
       UART0_Tx(*s++);
}


void UART0t_Str(char *s)
{
		y=0;
   while((ch1=UART0_Rx())!=0x0d){
       s[y]=ch1;
		   UART0_Tx(ch1);
		   //UART0_Str(buff);
		y++;}
	 UART0_Str("\r\n");
	 s[y]='\0';

}
