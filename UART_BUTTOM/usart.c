
#include "usart.h"
#include "stm32f10x.h"

volatile u8 Flag=FALSE;
volatile u16 Rx232buffer;
/**************************************************************************************
 * 描  述 : 初始化USART1并配置USART1中断优先级
 * 入  参 : 无
 * 返回值 : 无
 **************************************************************************************/
void USART1_Init(void)
{
	USART_InitTypeDef				USART_InitStructure;
	USART_ClockInitTypeDef  USART_ClockInitStructure;
	NVIC_InitTypeDef				NVIC_InitStructure;

	/* Enable the PWR/BKP Clock */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 , ENABLE);  
	
	USART_DeInit(USART1);          //将外设USART1寄存器重设为缺省值
	USART_InitStructure.USART_BaudRate = 19200;     //设置串口1波特率为19200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //设置一个帧中传输数据位 
	USART_InitStructure.USART_StopBits = USART_StopBits_1;     //定义发送的停止位数目为1
	USART_InitStructure.USART_Parity = USART_Parity_No;     //奇偶失能
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //硬件流控制失能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   //发送接收使能
	USART_Init(USART1, &USART_InitStructure);    

  USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;     //时钟低电平活动
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;         //设置SCLK引脚上时钟输出的极性为低电平
  USART_ClockInitStructure.USART_CPHA = USART_CPHA_1Edge;   //时钟第一个边沿进行数据捕获
  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;  //最后一位数据的时钟脉冲不从SCLK输出
  USART_ClockInit(USART1, &USART_ClockInitStructure); 
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //使能USART1接收中断
	USART_Cmd(USART1, ENABLE);      //使能USART1外设
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //NVIC_Group:NVIC分组 0~4 总共5组,最高2位抢占
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/*****************************/
void My_Usart1_Send(char *string){
    while(*string){
        /* 傳送訊息至 USART1 */
        USART_SendData(USART1, (unsigned short int) *string++);

        /* 等待訊息傳送完畢 */
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }
}

/**************************************************************************************
 * 描  述 : USART1发送函数
 * 入  参 : 单个字符
 * 返回值 : 无
 **************************************************************************************/
void USART1_SendByte(u8 byte)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
	USART_SendData(USART1, byte);
}

/**************************************************************************************
 * 描  述 : USART1接收到数据后串口发送出去
 * 入  参 : 无
 * 返回值 : 无
 **************************************************************************************/
void USART1_Tx_Puts(void)
{
  if(Flag)      //有新数据通过串口被接收到
	{
		My_Usart1_Send("fuck \n"); 
    //USART1_SendByte(Rx232buffer);  //发送字符
    USART1_SendByte(0x0D);    //发送换行符
    USART1_SendByte(0x0A);    //发送换行符	
		Flag=FALSE;     //清除接收标识符
  }
}

/**************************************************************************************
 * 描  述 : USART1全局中断服务
 * 入  参 : 无
 * 返回值 : 无
 **************************************************************************************/
void USART1_IRQHandler(void)
{  
  if(USART_GetITStatus(USART1,USART_IT_RXNE)!= RESET)  //接收中断
  {  
    Rx232buffer= USART_ReceiveData(USART1);     //通过外设USART1接收数据
		Flag=TRUE;                                     //接收到数据,接收标识符有效
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);  //清除USART1的中断待处理位
  }  
}





