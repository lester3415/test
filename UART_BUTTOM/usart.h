#include "stm32f10x.h"

#define	FALSE					0
#define	TRUE					1

extern  void USART1_Init(void);
extern  void USART1_Tx_Puts(void);
void My_Usart1_Send(char *string);
