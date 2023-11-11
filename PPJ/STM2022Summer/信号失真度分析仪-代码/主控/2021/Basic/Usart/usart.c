#include "usart.h"


//////////////////////////////////////////////////////
                /* ´¿Ú0 */
   //frequency  12M
const eUSCI_UART_Config uartConfig0 =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        6,                                      // BRDIV = 78
        8,                                       // UCxBRF = 2
        0x20,                                       // UCxBRS = 0
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

void Usart0tInit(void)
{
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9,
            GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_UART_initModule(EUSCI_A3_BASE, &uartConfig0);
    MAP_UART_enableModule(EUSCI_A3_BASE);  
}

void USART0PutChar(char ch)
{ 
	UART_transmitData(EUSCI_A3_BASE, ch); //·¢ËÍÊý¾Ý
}

void USART0PutString(char str[])
{ 
	while((*str)!= '\0')
	{
		USART0PutChar(*str++);
  }
}


//////////////////////////////////////////////////////
/*  ´¿Ú1  */ //115200
//frequency  12M

const eUSCI_UART_Config uartConfig1 =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        6,                                      // BRDIV = 6
        8,                                       // UCxBRF = 8
        0x20,                                       // UCxBRS = 0??
        EUSCI_A_UART_NO_PARITY,                  // ÎÞÆæÅ¼Ð£Ñé
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

void Usart1tInit(void)
{   
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
            GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_UART_initModule(EUSCI_A2_BASE, &uartConfig1);
    MAP_UART_enableModule(EUSCI_A2_BASE); 
}
 
void USART1PutChar(char ch)
{ 
	UART_transmitData(EUSCI_A2_BASE, ch); //·¢ËÍÊý¾Ý
}

void USART1PutString(char str[])
{ 
	while((*str)!= '\0')
	{
		USART1PutChar(*str++);
  }
}

