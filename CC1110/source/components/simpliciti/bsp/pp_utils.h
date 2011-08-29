/**************************************************************************************************
  Filename:       pp_utils.h
  Revised:        $Date: 2009-08-17 10:50:58 -0700 (Mon, 17 Aug 2009) $
  Author:         $Author: jnoxon $

  Description:    This header file defines macros used by the UART driver and
                  extended SoC header files.

  Copyright 2004-2009 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights granted under
  the terms of a software license agreement between the user who downloaded the software,
  his/her employer (which must be your employer) and Texas Instruments Incorporated (the
  "License"). You may not use this Software unless you agree to abide by the terms of the
  License. The License limits your use, and you acknowledge, that the Software may not be
  modified, copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio frequency
  transceiver, which is integrated into your product. Other than for the foregoing purpose,
  you may not use, reproduce, copy, prepare derivative works of, modify, distribute,
  perform, display or sell this Software and/or its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS”
  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY
  WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
  IN NO EVENT SHALL TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE
  THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY
  INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST
  DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY
  THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/

#ifndef pp_utils_h
#define pp_utils_h

/******************************************************************************/
/* General utility macros                                                     */
/******************************************************************************/

/* the following macro will stringize the passed parameter   
 * Example: STRINGIZE( hello ) ==> "hello" */
#define STRINGIZE( s ) STRINGIZE_X( s )
#define STRINGIZE_X( s ) #s

/* the following macro will concatenate to parameters into a single parameter   
 * or identifier
 * Example: CONCATENATE( GOOD, BYE ) ==> GOODBYE */
#define CONCATENATE( a, b ) CONCATENATE_X( a, b )
#define CONCATENATE_X( a, b ) a ## b

/* the following macro will concatenate two items infixed with the middle item   
 * Example: INFIX( ANOTHER, _, TOKEN ) ==> ANOTHER_TOKEN */
#define INFIX( a, i, b ) CONCATENATE( CONCATENATE( a, i ), b )



/******************************************************************************/
/* macros for declaring bit field uinons                                      */
/******************************************************************************/

/* the following macro creates a union of with an encompasing group variable
 * and a structure of bit fields.  the flds parameter most likely will be
 * a DECL_BIT_FIELDS_x macro or a DECL_WIDTH_BIT_FIELDS_x macro or a semicolon
 * delimited list of any combination of the two */

#if ( defined __IAR_SYSTEMS_ICC__ ) && ( defined __ICC8051__ )

#define DECL_BIT_FIELD_UNION( u_tag, u_name, grp_type, grp_name, flds_name, ... ) \
  union u_tag { grp_type grp_name; struct { __VA_ARGS__; } flds_name; } u_name

#endif

/* the following macros define forms for declaring bit fields of a common type
 * and common width
 * Example: DECL_WIDTH_BIT_FIELDS_3( unsigned char, 2, a, , b );
 * effectively yeilds...
 *   unsigned char a : 2;
 *   unsigned char   : 2;
 *   unsigned char b : 2;
 * NOTE: the second field has no name and is therefore a reserved field */
#define DECL_WIDTH_BIT_FIELDS_1( t, w, f ) DECL_BIT_FIELDS_1( t, f, w )
#define DECL_WIDTH_BIT_FIELDS_2( t, w, f1, f0 ) DECL_BIT_FIELDS_2( t, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_3( t, w, f2, f1, f0 ) DECL_BIT_FIELDS_3( t, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_4( t, w, f3, f2, f1, f0 ) DECL_BIT_FIELDS_4( t, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_5( t, w, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_5( t, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_6( t, w, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_6( t, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_7( t, w, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_7( t, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_8( t, w, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_8( t, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_9( t, w, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_9( t, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_10( t, w, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_10( t, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_11( t, w, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_11( t, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_12( t, w, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_12( t, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_13( t, w, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_13( t, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_14( t, w, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_14( t, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_15( t, w, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_15( t, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_16( t, w, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_16( t, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_17( t, w, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_17( t, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_18( t, w, f17, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_18( t, f17, w, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_19( t, w, f18, f17, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_19( t, f18, w, f17, w, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_20( t, w, f19, f18, f17, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_20( t, f19, w, f18, w, f17, w, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_21( t, w, f20, f19, f18, f17, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_21( t, f20, w, f19, w, f18, w, f17, w, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_22( t, w, f21, f20, f19, f18, f17, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_22( t, f21, w, f20, w, f19, w, f18, w, f17, w, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_23( t, w, f22, f21, f20, f19, f18, f17, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_23( t, f22, w, f21, w, f20, w, f19, w, f18, w, f17, w, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_24( t, w, f23, f22, f21, f20, f19, f18, f17, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_24( t, f23, w, f22, w, f21, w, f20, w, f19, w, f18, w, f17, w, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_25( t, w, f24, f23, f22, f21, f20, f19, f18, f17, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_25( t, f24, w, f23, w, f22, w, f21, w, f20, w, f19, w, f18, w, f17, w, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_26( t, w, f25, f24, f23, f22, f21, f20, f19, f18, f17, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_26( t, f25, w, f24, w, f23, w, f22, w, f21, w, f20, w, f19, w, f18, w, f17, w, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_27( t, w, f26, f25, f24, f23, f22, f21, f20, f19, f18, f17, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_27( t, f26, w, f25, w, f24, w, f23, w, f22, w, f21, w, f20, w, f19, w, f18, w, f17, w, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_28( t, w, f27, f26, f25, f24, f23, f22, f21, f20, f19, f18, f17, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_28( t, f27, w, f26, w, f25, w, f24, w, f23, w, f22, w, f21, w, f20, w, f19, w, f18, w, f17, w, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_29( t, w, f28, f27, f26, f25, f24, f23, f22, f21, f20, f19, f18, f17, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_29( t, f28, w, f27, w, f26, w, f25, w, f24, w, f23, w, f22, w, f21, w, f20, w, f19, w, f18, w, f17, w, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_30( t, w, f29, f28, f27, f26, f25, f24, f23, f22, f21, f20, f19, f18, f17, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_30( t, f29, w, f28, w, f27, w, f26, w, f25, w, f24, w, f23, w, f22, w, f21, w, f20, w, f19, w, f18, w, f17, w, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_31( t, w, f30, f29, f28, f27, f26, f25, f24, f23, f22, f21, f20, f19, f18, f17, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_31( t, f30, w, f29, w, f28, w, f27, w, f26, w, f25, w, f24, w, f23, w, f22, w, f21, w, f20, w, f19, w, f18, w, f17, w, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )
#define DECL_WIDTH_BIT_FIELDS_32( t, w, f31, f30, f29, f28, f27, f26, f25, f24, f23, f22, f21, f20, f19, f18, f17, f16, f15, f14, f13, f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0 ) DECL_BIT_FIELDS_32( t, f31, w, f30, w, f29, w, f28, w, f27, w, f26, w, f25, w, f24, w, f23, w, f22, w, f21, w, f20, w, f19, w, f18, w, f17, w, f16, w, f15, w, f14, w, f13, w, f12, w, f11, w, f10, w, f9, w, f8, w, f7, w, f6, w, f5, w, f4, w, f3, w, f2, w, f1, w, f0, w )

/* the following macros define sets of bit fields with a common type
 * the t parameter is the type to use for all bit fields
 * the fx parameter is the name of the bit fields
 * the wx parameter is the width of bit field fx
 * Example: DECL_BIT_FIELDS_3( unsigned char, a, 2, , 5, b, 1 );
 * effectively yeilds...
 *   unsigned char a : 2;
 *   unsigned char   : 5;
 *   unsigned char b : 1;
 * NOTE: the second field has no name and is therefore a reserved field */
#define DECL_BIT_FIELDS_1(  t, f, w ) t f : w
#define DECL_BIT_FIELDS_2(  t, f1, w1, f0, w0 ) DECL_BIT_FIELDS_1( t, f0, w0 ); DECL_BIT_FIELDS_1( t, f1, w1 )
#define DECL_BIT_FIELDS_3(  t, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_2( t, f1, w1, f0, w0 ); DECL_BIT_FIELDS_1( t, f2, w2 )
#define DECL_BIT_FIELDS_4(  t, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_2( t, f1, w1, f0, w0 ); DECL_BIT_FIELDS_2( t, f3, w3, f2, w2 )
#define DECL_BIT_FIELDS_5(  t, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_3( t, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_2( t, f4, w4, f3, w3 )
#define DECL_BIT_FIELDS_6(  t, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_3( t, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_3( t, f5, w5, f4, w4, f3, w3 )
#define DECL_BIT_FIELDS_7(  t, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_4( t, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_3( t, f6, w6, f5, w5, f4, w4 )
#define DECL_BIT_FIELDS_8(  t, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_4( t, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_4( t, f7, w7, f6, w6, f5, w5, f4, w4 )
#define DECL_BIT_FIELDS_9(  t, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_5( t, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_4( t, f8, w8, f7, w7, f6, w6, f5, w5 )
#define DECL_BIT_FIELDS_10( t, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_5( t, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_5( t, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5 )
#define DECL_BIT_FIELDS_11( t, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_6( t, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_5( t, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6 )
#define DECL_BIT_FIELDS_12( t, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_6( t, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_6( t, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6 )
#define DECL_BIT_FIELDS_13( t, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_7( t, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_6( t, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7 )
#define DECL_BIT_FIELDS_14( t, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_7( t, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_7( t, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7 )
#define DECL_BIT_FIELDS_15( t, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_8( t, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_7( t, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8 )
#define DECL_BIT_FIELDS_16( t, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_8( t, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_8( t, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8 )
#define DECL_BIT_FIELDS_17( t, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_9( t, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_8( t, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9 )
#define DECL_BIT_FIELDS_18( t, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_9( t, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_9( t, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9 )
#define DECL_BIT_FIELDS_19( t, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_10( t, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_9( t, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10 )
#define DECL_BIT_FIELDS_20( t, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_10( t, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_10( t, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10 )
#define DECL_BIT_FIELDS_21( t, f20, w20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_11( t, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_10( t, f20, f20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11 )
#define DECL_BIT_FIELDS_22( t, f21, w21, f20, w20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_11( t, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_11( t, f21, w21, f20, f20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11 )
#define DECL_BIT_FIELDS_23( t, f22, w22, f21, w21, f20, w20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_12( t, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_11( t, f22, w22, f21, w21, f20, f20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12 )
#define DECL_BIT_FIELDS_24( t, f23, w23, f22, w22, f21, w21, f20, w20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_12( t, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_12( t, f23, w23, f22, w22, f21, w21, f20, f20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12 )
#define DECL_BIT_FIELDS_25( t, f24, w24, f23, w23, f22, w22, f21, w21, f20, w20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_13( t, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_12( t, f24, w24, f23, w23, f22, w22, f21, w21, f20, f20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13 )
#define DECL_BIT_FIELDS_26( t, f25, w25, f24, w24, f23, w23, f22, w22, f21, w21, f20, w20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_13( t, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_13( t, f25, w25, f24, w24, f23, w23, f22, w22, f21, w21, f20, f20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13 )
#define DECL_BIT_FIELDS_27( t, f26, w26, f25, w25, f24, w24, f23, w23, f22, w22, f21, w21, f20, w20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_14( t, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_13( t, f26, w26, f25, w25, f24, w24, f23, w23, f22, w22, f21, w21, f20, f20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14 )
#define DECL_BIT_FIELDS_28( t, f27, w27, f26, w26, f25, w25, f24, w24, f23, w23, f22, w22, f21, w21, f20, w20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_14( t, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_14( t, f27, w27, f26, w26, f25, w25, f24, w24, f23, w23, f22, w22, f21, w21, f20, f20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14 )
#define DECL_BIT_FIELDS_29( t, f28, w28, f27, w27, f26, w26, f25, w25, f24, w24, f23, w23, f22, w22, f21, w21, f20, w20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_15( t, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_14( t, f28, w28, f27, w27, f26, w26, f25, w25, f24, w24, f23, w23, f22, w22, f21, w21, f20, f20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15 )
#define DECL_BIT_FIELDS_30( t, f29, w29, f28, w28, f27, w27, f26, w26, f25, w25, f24, w24, f23, w23, f22, w22, f21, w21, f20, w20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_15( t, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_15( t, f29, w29, f28, w28, f27, w27, f26, w26, f25, w25, f24, w24, f23, w23, f22, w22, f21, w21, f20, f20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15 )
#define DECL_BIT_FIELDS_31( t, f30, w30, f29, w29, f28, w28, f27, w27, f26, w26, f25, w25, f24, w24, f23, w23, f22, w22, f21, w21, f20, w20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_16( t, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_15( t, f30, w30, f29, w29, f28, w28, f27, w27, f26, w26, f25, w25, f24, w24, f23, w23, f22, w22, f21, w21, f20, f20, f19, w19, f18, w18, f17, w17, f16, w16 )
#define DECL_BIT_FIELDS_32( t, f31, w31, f30, w30, f29, w29, f28, w28, f27, w27, f26, w26, f25, w25, f24, w24, f23, w23, f22, w22, f21, w21, f20, w20, f19, w19, f18, w18, f17, w17, f16, w16, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ) DECL_BIT_FIELDS_16( t, f15, w15, f14, w14, f13, w13, f12, w12, f11, w11, f10, w10, f9, w9, f8, w8, f7, w7, f6, w6, f5, w5, f4, w4, f3, w3, f2, w2, f1, w1, f0, w0 ); DECL_BIT_FIELDS_16( t, f31, w31, f30, w30, f29, w29, f28, w28, f27, w27, f26, w26, f25, w25, f24, w24, f23, w23, f22, w22, f21, w21, f20, f20, f19, w19, f18, w18, f17, w17, f16, w16 )

#endif
