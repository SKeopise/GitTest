#include <usart.h>

uint8_t Serial_TxPacket[4];
uint8_t Serial_RxPacket[4];

char RxPacket_Char[50];

//uint8_t serial_RxData;
uint8_t serial_RxFlag;


void USART1_IRQHandler()
{
	String_RxData();
}



void usart_init(u32 bound)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA,ENABLE);
	
	USART_DeInit(USART1);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	
	USART_Init(USART1,&USART_InitStructure);
	

	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	
	USART_Cmd(USART1,ENABLE);
	
}


void Serial_SendByte(uint8_t Byte)
{
	USART_ClearFlag(USART1,USART_FLAG_TC);
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET); 

}

void Serial_SendArray(uint8_t *Array,uint16_t Length)
{
	uint16_t i;
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Array[i]);
	}
}


void Serial_SendString(char *String)
{
	uint16_t i;
	for(i=0;String[i] != '\0';i++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X,uint32_t Y)
{
	uint32_t Result = 1;
	
	while(Y--)
	{
		Result *= X;
	}
	
	return Result;
}

void Serial_SendNumber(uint32_t Number,uint8_t Length)
{
	uint8_t i=0;
	
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Number /Serial_Pow(10,Length-i-1) % 10 + '0');
	}
}

int fputc(int ch,FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char* format,...)
{
	char String[100];
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
	
	va_end(arg);
	Serial_SendString(String);	
}




uint8_t Serial_GetRxFlag()
{
	if(serial_RxFlag == 1)
	{
		serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

//uint8_t Serial_GetRxData()
//{
//	return serial_RxData;
//}





void Serial_SendPacket()
{
	Serial_SendByte(0xFF);
	Serial_SendArray(Serial_TxPacket,4);
	Serial_SendByte(0xFE);
}



void Hex_RxData()
{
	static uint8_t RxState = 0;
	static uint8_t PRxPacket = 0;
	
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE) == SET)
	{
//		serial_RxData = USART_ReceiveData(USART1);
//		serial_RxFlag = 1;
		uint8_t RxData = USART_ReceiveData(USART1);
		
		if(RxState == 0)
		{
			if(RxData == 0xFF)
			{
				RxState = 1;
				PRxPacket = 0;
			}
		}
		else if(RxState == 1)
		{
			Serial_RxPacket[PRxPacket] = RxData;
			PRxPacket++;
			if(PRxPacket >= 4)
			{
				RxState = 2;
			}
		}
		else if(RxState == 2)
		{
			if(RxData == 0xFE)
			{
				RxState = 0;
				serial_RxFlag = 1;
			}
		}
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}


void String_RxData()
{
	static uint8_t RxState = 0;
	static uint8_t PRxPacket = 0;
	
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE) == SET)
	{
//		serial_RxData = USART_ReceiveData(USART1);
//		serial_RxFlag = 1;
		uint8_t RxData = USART_ReceiveData(USART1);
		
		if(RxState == 0)
		{
			if(RxData == '@' && serial_RxFlag == 0)
			{
				RxState = 1;
				PRxPacket = 0;
			}
		}
		else if(RxState == 1)
		{
			if(RxData == '\r')
			{
				RxState = 2;
			}
			else
			{
				RxPacket_Char[PRxPacket] = RxData;
				PRxPacket++;
			}
		}
		else if(RxState == 2)
		{
			if(RxData == '\n')
			{
				RxState = 0;
				serial_RxFlag = 1;
				RxPacket_Char[PRxPacket] = '\0';
			}
		}
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}















