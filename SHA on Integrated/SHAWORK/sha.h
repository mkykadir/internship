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

#include <stdint.h>

#ifndef __SHA_H_
#define __SHA_H_

#define SHA_VERSION "1.0"

// undefine/comment these out to NOT include support for them
#define SHA160 
#define SHA224 
#define SHA256 
#define SHA384 
#define SHA512 

/* First four bits are the SHA mode select */
#define MODE_SHA_160   0x01
#define MODE_SHA_224   0x02
#define MODE_SHA_256   0x03
#define MODE_SHA_384   0x04
#define MODE_SHA_512   0x05
#define MODE_MASK(x)   (x & 0x0f)

/* OR in these options to enable specific feature */
#define MODE_HW_ACCEL  0x80

#define SHA_ERROR_NOTSUPPORTED     -1
#define SHA_OK                      0

typedef struct sha_msg_frags_s {
  uint8_t *message;
  uint16_t length;
  struct sha_msg_frags_s *next_frag;
} sha_msg_frags;

int16_t sha_createHash(uint8_t* message, uint16_t length, uint8_t* output, 
                uint8_t mode);

int16_t sha_createHash_multi(sha_msg_frags *frags, uint8_t* output, uint8_t mode);

#endif
