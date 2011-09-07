/*****************************************************************************
 *   Echo back data that are received on the UART.
 *
 *   Copyright(C) 2010, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include "uart.h"
#include "timer32.h"
#include "type.h"

volatile uint32_t UARTStatus;
volatile uint8_t UARTTxEmpty = 1;
volatile uint8_t UARTBuffer[BUFSIZE];
volatile uint32_t UARTCount = 0;

/*****************************************************************************
 ** Function name:		UART_IRQHandler
 **
 ** Descriptions:		UART interrupt handler
 **
 ** parameters:			None
 ** Returned value:		None
 **
 *****************************************************************************/

void UART_IRQHandler(void) {
	uint8_t IIRValue, LSRValue;
	uint8_t Dummy = Dummy;

	IIRValue = LPC_UART->IIR;

	IIRValue >>= 1; /* skip pending bit in IIR */
	IIRValue &= 0x07; /* check bit 1~3, interrupt identification */
	if (IIRValue == IIR_RLS) /* Receive Line Status */
	{
		LSRValue = LPC_UART->LSR;
		/* Receive Line Status */
		if (LSRValue & (LSR_OE | LSR_PE | LSR_FE | LSR_RXFE | LSR_BI)) {
			/* There are errors or break interrupt */
			/* Read LSR will clear the interrupt */
			UARTStatus = LSRValue;
			Dummy = LPC_UART->RBR; /* Dummy read on RX to clear
			 interrupt, then bail out */
			return;
		}
		if (LSRValue & LSR_RDR) /* Receive Data Ready */
		{
			/* If no error on RLS, normal ready, save into the data buffer. */
			/* Note: read RBR will clear the interrupt */
			UARTBuffer[UARTCount++] = LPC_UART->RBR;
			if (UARTCount == BUFSIZE) {
				UARTCount = 0; /* buffer overflow */
			}
		}
	} else if (IIRValue == IIR_RDA) /* Receive Data Available */
	{
		/* Receive Data Available */
		UARTBuffer[UARTCount++] = LPC_UART->RBR;
		if (UARTCount == BUFSIZE) {
			UARTCount = 0; /* buffer overflow */
		}
	} else if (IIRValue == IIR_CTI) /* Character timeout indicator */
	{
		/* Character Time-out indicator */
		UARTStatus |= 0x100; /* Bit 9 as the CTI error */
	} else if (IIRValue == IIR_THRE) /* THRE, transmit holding register empty */
	{
		/* THRE interrupt */
		LSRValue = LPC_UART->LSR; /* Check status in the LSR to see if
		 valid data in U0THR or not */
		if (LSRValue & LSR_THRE) {
			UARTTxEmpty = 1;
		} else {
			UARTTxEmpty = 0;
		}
	}
	return;
}

int main(void) {
	init_timer32(0, 10);
	UARTInit(115200);
	// Enable the UART Interrupt
	NVIC_EnableIRQ(UART_IRQn);
	LPC_UART->IER = IER_RBR | IER_RLS;

	while (1) {
		// If we receive data, echo back
		if (UARTCount != 0) {
			UARTSend((uint8_t*) UARTBuffer, UARTCount);
			UARTCount = 0;
		}

		delay32Ms(0, 10);
	}
	return 0;
}
