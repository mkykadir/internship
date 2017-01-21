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
 * \file serial.h
 * \brief Provides functions to initialize and putchar to serial port
 *
 * Serial functions header file
 *
 */

/***********************************/
// Serial Settings
/***********************************/
#define serial_baud 115200
#define SYS_CLK     12000000L
#define SERIAL_SMOD 0x02
#define SERIAL_ECHO
/***********************************/

/**
 * Initialize the Serial port with the above parameters
 */
void serial_init(void);

/**
 * Print a character to the serial port, used by printf routines
 */
int __putchar(int);

/**
 * Get a character from the serial port, used by scanf routines
 * Optionally allows characters to be echoed back to source via
 * define SERIAL_ECHO
 */
char __getchar(void);
