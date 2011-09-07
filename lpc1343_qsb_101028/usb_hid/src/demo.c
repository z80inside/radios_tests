/*----------------------------------------------------------------------------
 *      Name:    DEMO.C
 *      Purpose: USB HID Demo
 *      Version: V1.20
 *----------------------------------------------------------------------------
 *      This software is supplied "AS IS" without any warranties, express,
 *      implied or statutory, including but not limited to the implied
 *      warranties of fitness for purpose, satisfactory quality and
 *      noninfringement. Keil extends you a royalty-free right to reproduce
 *      and distribute executable files created using this software for use
 *      on NXP Semiconductors LPC microcontroller devices only. Nothing else 
 *      gives you the right to use this software.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "lpc13xx.h"                        /* LPC13xx definitions */
#include "type.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
//#include "gpio.h"
//#include "timer16.h"
#include "demo.h"

extern volatile uint32_t timer16_0_counter;

uint8_t InReport;                           /* HID Input Report    */
                                            /*   Bit0   : Buttons  */
                                            /*   Bit1..7: Reserved */

uint8_t OutReport;                          /* HID Out Report      */
                                            /*   Bit0..7: LEDs     */


/*
 *  Get HID Input Report -> InReport
 */

void GetInReport (void) {
  if ( LPC_GPIO0->DATA & (1<<1) ) {		/* Check if PBINT is pressed */
    InReport = 0x01;
  } else {
    InReport = 0x00;
  }
  return;
}


/*
 *  Set HID Output Report <- OutReport
 */

void SetOutReport (void) {
  /* port2, bit 0~3 are used as LED indication from
  HID utility. */
//  LPC_GPIO2->DATA &= ~(0x0F<<0);
//  LPC_GPIO2->DATA |= (OutReport<<0);
  return; 
}


/* Main Program */

int main (void) 
{  
  SystemInit();

  USBIOClkConfig();

  /* P0.1 is push-button input, P2.0~3 are LED output. */
//  LPC_GPIO2->DIR |= (0x1<<0)|(0x1<<1)|(0x1<<2)|(0x1<<3);
//  LPC_GPIO0->DIR &= ~(0x1<<1);

  /* 16-bit timer 0. */
//  init_timer16(0, /*TIME_INTERVAL*/10);
//  enable_timer16(0);

  /* Set port 2_0 to output */
//  GPIOSetDir( 2, 0, 1 );
  USB_Init();                               /* USB Initialization */
  USB_Connect(TRUE);                        /* USB Connect */

  while (1)                                /* Loop forever */
  {
#if 0
	/* I/O configuration and LED setting pending. */
	if ( (timer16_0_counter > 0) && (timer16_0_counter <= 200) )
	{
	  GPIOSetValue( 2, 0, 0 );
	}
	if ( (timer16_0_counter > 200) && (timer16_0_counter <= 400) )
	{
	  GPIOSetValue( 2, 0, 1 );
	}
	else if ( timer16_0_counter > 400 )
	{
	  timer16_0_counter = 0;
	}
#endif
  }

}
