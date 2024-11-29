#ifndef _UART_H_
#define _UART_H_

void InitUART0 (void); 
void UART0_Tx(char ch);  
char UART0_Rx(void); 
void UART0_Str(char *);
void UART0t_Str(char *s);
#endif
