#include "stm32f10x.h"





int main(void){
    /******** 宣告 USART、GPIO 結構體 ********/
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
    /******** 啟用 GPIOA、USART1 的 RCC 時鐘 ********/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);

	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0; 
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;	//┰
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		
		GPIO_Init(GPIOA, &GPIO_InitStructure);  //秈︽GPIO挡篶爹
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);    //рEXTI0硈PA0弧琌盢GPIOA.0爹い耞絬EXTILine0
	
		EXTI_InitStructure.EXTI_Line = EXTI_Line0;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
	
		NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;			// 0x01
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;								// 0x00
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure); 
		
		
    /******** 設定 PA9 為 Tx 覆用 ********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

    GPIO_Init(GPIOA, &GPIO_InitStructure); // 初始化 PA9

    /******** 設定 PA10 為 Rx 覆用 ********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(GPIOA, &GPIO_InitStructure); // 初始化 PA10


    /******** USART 基本參數設定 ********/

    USART_InitStructure.USART_BaudRate = 19200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure); // 初始化 UART1

    USART_Cmd(USART1, ENABLE); // 啟用 USART1


    while(1){ 
			
    }

}
