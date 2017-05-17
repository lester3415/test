
#include "usart.h"
#include "stm32f10x.h"

volatile u8 Flag=FALSE;
volatile u16 Rx232buffer;
/**************************************************************************************
 * ��  �� : ��ʼ��USART1������USART1�ж����ȼ�
 * ��  �� : ��
 * ����ֵ : ��
 **************************************************************************************/
void USART1_Init(void)
{
	USART_InitTypeDef				USART_InitStructure;
	USART_ClockInitTypeDef  USART_ClockInitStructure;
	NVIC_InitTypeDef				NVIC_InitStructure;

	/* Enable the PWR/BKP Clock */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 , ENABLE);  
	
	USART_DeInit(USART1);          //������USART1�Ĵ�������Ϊȱʡֵ
	USART_InitStructure.USART_BaudRate = 19200;     //���ô���1������Ϊ19200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //����һ��֡�д�������λ 
	USART_InitStructure.USART_StopBits = USART_StopBits_1;     //���巢�͵�ֹͣλ��ĿΪ1
	USART_InitStructure.USART_Parity = USART_Parity_No;     //��żʧ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //Ӳ��������ʧ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   //���ͽ���ʹ��
	USART_Init(USART1, &USART_InitStructure);    

  USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;     //ʱ�ӵ͵�ƽ�
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;         //����SCLK������ʱ������ļ���Ϊ�͵�ƽ
  USART_ClockInitStructure.USART_CPHA = USART_CPHA_1Edge;   //ʱ�ӵ�һ�����ؽ������ݲ���
  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;  //���һλ���ݵ�ʱ�����岻��SCLK���
  USART_ClockInit(USART1, &USART_ClockInitStructure); 
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //ʹ��USART1�����ж�
	USART_Cmd(USART1, ENABLE);      //ʹ��USART1����
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //NVIC_Group:NVIC���� 0~4 �ܹ�5��,���2λ��ռ
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/*****************************/
void My_Usart1_Send(char *string){
    while(*string){
        /* ����ӍϢ�� USART1 */
        USART_SendData(USART1, (unsigned short int) *string++);

        /* �ȴ�ӍϢ�����ꮅ */
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }
}

/**************************************************************************************
 * ��  �� : USART1���ͺ���
 * ��  �� : �����ַ�
 * ����ֵ : ��
 **************************************************************************************/
void USART1_SendByte(u8 byte)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
	USART_SendData(USART1, byte);
}

/**************************************************************************************
 * ��  �� : USART1���յ����ݺ󴮿ڷ��ͳ�ȥ
 * ��  �� : ��
 * ����ֵ : ��
 **************************************************************************************/
void USART1_Tx_Puts(void)
{
  if(Flag)      //��������ͨ�����ڱ����յ�
	{
		My_Usart1_Send("fuck \n"); 
    //USART1_SendByte(Rx232buffer);  //�����ַ�
    USART1_SendByte(0x0D);    //���ͻ��з�
    USART1_SendByte(0x0A);    //���ͻ��з�	
		Flag=FALSE;     //������ձ�ʶ��
  }
}

/**************************************************************************************
 * ��  �� : USART1ȫ���жϷ���
 * ��  �� : ��
 * ����ֵ : ��
 **************************************************************************************/
void USART1_IRQHandler(void)
{  
  if(USART_GetITStatus(USART1,USART_IT_RXNE)!= RESET)  //�����ж�
  {  
    Rx232buffer= USART_ReceiveData(USART1);     //ͨ������USART1��������
		Flag=TRUE;                                     //���յ�����,���ձ�ʶ����Ч
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);  //���USART1���жϴ�����λ
  }  
}





