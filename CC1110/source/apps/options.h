/**************************************************************************************************
  Filename:       options.h
  Revised:        $Date: 2009-08-17 10:50:58 -0700 (Mon, 17 Aug 2009) $
  Author:         $Author: jnoxon $

  Description:    This header file defines the UART driver settings and other
                  desired project options.

  Copyright 2004-2009 Texas Instruments Incorporated. All rights reserved.
**************************************************************************************************/

#ifndef OPTIONS_H
#define OPTIONS_H

/* ------------------------------------------------------------------------------------------------
 *                                UART Settings
 * ------------------------------------------------------------------------------------------------
 */ 
#define RX_TX_BUFFER_SIZE  50      /* Size of transmit FIFO and receive FIFO */
#define UART_BAUD_RATE     115200
#define UART_FLOW_CONTROL  UART_FLOW_CONTROL_OFF  /* _ON or _OFF */
#define UART_PARITY_MODE   UART_PARITY_NONE      /* _NONE, _EVEN, or _ODD */ 
#define UART_STOP_BITS     UART_1_STOP_BIT       /* _1_STOP_BIT or _2_STOP_BITS */


/* ------------------------------------------------------------------------------------------------
 *                                8051-Specific Settings
 * ------------------------------------------------------------------------------------------------
 */ 

#if ( defined __ICC8051__ )

/* Specify USART module to use for UART:
 *   If using an 8051-based SoC on a SmartRF®04 and SmartRF®05 board, choose 
 *   UART_NUMBER = UART_NUMBER_0      and      UART_LOCATION = UART_LOCATION_1
 *   to map UART to on-board RS-232 transceivers for serial communication  */ 
  
  #define UART_NUMBER     UART_NUMBER_0          // _0 or _1
  #define UART_LOCATION   UART_LOCATION_1        // _1 or _2



/* ------------------------------------------------------------------------------------------------
 *                                MSP430-Specific Settings
 * ------------------------------------------------------------------------------------------------
 */

#elif ( defined __ICC430__ ) || ( defined __TI_COMPILER_VERSION__)

/* Specify USCI module to use for UART:
 *   On both MSP430FG4618/F2013 Experimenter Board and CCMSP-EM430F2618 
 *   Daughter Board for SmartRF®05 board, to map to RS-232:
 *   UART_LETTER = A     UART_MODULE = 0    */
  
  #define UART_LETTER       A     /* Currently, use UART module USCI_A0 */
  #define UART_MODULE       0

/*  Specify RX and TX pins of the chosen USCI module:
 *   On MSP430FG4618/F2013 Experimenter Board, to map to RS-232:
 *   TX pin = P2.4     RX pin = P2.5        
 *   On CCMSP-EM430F2618 Daughter Board for SmartRF®05 board, to map to RS-232:
 *   TX pin = P3.4     RX pin = P3.5     */
  
  #define UART_TX_PORT_NUM  3    
  #define UART_TX_BIT_NUM   4    
  #define UART_RX_PORT_NUM  3    
  #define UART_RX_BIT_NUM   5    
  
/*  Specify two I/O pins as CTS and RTS UART pins for hardware-handshaking:
 *   On CCMSP-EM430F2618 Daughter Board for SmartRF®05 board, to map to RS-232:
 *   CTS pin = P2.7    RTS pin = P2.6       */
  
  #define UART_CTS_PORT_NUM 2    /* If flow control is ON, these two pins     */  
  #define UART_CTS_BIT_NUM  7    /* will be mapped as CTS and RTS, otherwise  */
  #define UART_RTS_PORT_NUM 2    /* these pins will be left unmapped          */
  #define UART_RTS_BIT_NUM  6
  
/* Cross-map definitions (Do Not Change) */ 
  #define UART_NUMBER     UART_LETTER	
  #define UART_LOCATION	  UART_MODULE
#endif

#endif
