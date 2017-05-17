#include "stm32f10x.h"





int main(void){
    /******** ���� USART��GPIO �Y���w ********/
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
    /******** ���� GPIOA��USART1 �� RCC �r� ********/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);

	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0; 
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;	//�W��
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		
		GPIO_Init(GPIOA, &GPIO_InitStructure);  //�i��GPIO���c���U
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);    //��EXTI0�s��PA0�A�]�i�H���O�NGPIOA.0���U�ܤ��_�uEXTILine0
	
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
		
		
    /******** �O�� PA9 �� Tx ���� ********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

    GPIO_Init(GPIOA, &GPIO_InitStructure); // ��ʼ�� PA9

    /******** �O�� PA10 �� Rx ���� ********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(GPIOA, &GPIO_InitStructure); // ��ʼ�� PA10


    /******** USART ���������O�� ********/

    USART_InitStructure.USART_BaudRate = 19200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure); // ��ʼ�� UART1

    USART_Cmd(USART1, ENABLE); // ���� USART1


    while(1){ 
			
    }

}
