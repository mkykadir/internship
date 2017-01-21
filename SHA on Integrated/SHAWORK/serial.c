/*----------------------------------------------------------------------------
 *  Copyright (C) 2009 Maxim Integrated Products Incorporated, All Rights Reserved.
 * 
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included
 *  in all copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 *  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY,  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *  IN NO EVENT SHALL MAXIM INTEGRATED PRODUCTS BE LIABLE FOR ANY CLAIM, DAMAGES
 *  OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 * 
 *  Except as contained in this notice, the name of Maxim Integrated Products
 *  shall not be used except as stated in the Maxim Integrated Products
 *  Branding Policy.
 * ---------------------------------------------------------------------------
 */
    
/** 
 * \file serial.c
 * \brief Provides functions to initialize and putchar to serial port
 *
 * This file provides a function to initialize the serial ports of the MAXQ1850
 * used on the MAXQ1850 Evaluation Kit board. It also provides the low-level
 * functions for reading/writing serial ports
 *
 */

#include <MAXQ1850.H>
#include "serial.h"


//---------------------------------------------------------------------------
// Function: serial_init
//  Summary: Initializes serial port 0 in 10-bit asynchronous mode, 115200 baud.
//   Inputs: None
//   Output: None
//---------------------------------------------------------------------------
void serial_init(void)
{
   unsigned long pr_val;

   // Calculate Serial Baud rate
   pr_val = serial_baud * (double)8388608.0 / (double)SYS_CLK;

   SCON = (1<<6) | (1<<4) | 2;   // Set to mode 1 (10-bit asynchronous) and enable
                                 // Pre set transmit flag
   SMD  = 2;                     // Baud rate = 16 x baud clock

   PD1 |= 2;                     // Set transmist pin to output mode to avoid droopy bus

   if(pr_val > 0xFFFF)
   {
        SMD |= SERIAL_SMOD;
        PR = (serial_baud * ((double)(8388608.0/4.0) / (double)SYS_CLK));
   }
   else
   {
        SMD &= (~SERIAL_SMOD);
        PR = pr_val;
   }

   SCON &= ~1;                   // Clear Receive character flag 
   return;
}

//Standard putchar routine needed for printf
//Called automatically from stdio
//Note, requires calling serial_init before use
int __putchar(int ch)
{
  /* Stall until last transmit has completed  */
  while (!(SCON & 0x02));
  
  /* Clear the TI bit */ 
  SCON &= ~2;

  /* Send it out */
  SBUF = (char)ch;      

  if (ch == 10)          // If output char is a line feed
  {
    /* Stall until last transmit has completed  */
    while (!(SCON & 0x02));
    
    /* Clear the TI bit */ 
    SCON &= ~2;
  
    /* Send it out */
    SBUF = (char)13;  
  }
    
  return ch;
}

//Reads one byte from serial0 uart
char __getchar(void)
{
#ifdef SERIAL_ECHO
   char in;
#endif
   while (!(SCON & 1));          // Wait for receive complete flag to be set
   SCON &= ~1;                   // Clear receive complete flag

#ifdef SERIAL_ECHO
   in = SBUF;
   /* Stall until last transmit has completed  */
   while (!(SCON & 0x02));
    
   /* Clear the TI bit */ 
   SCON &= ~2;
  
   /* Send it out */
   SBUF = in;
   
   return in;
#endif
   return SBUF;
}
