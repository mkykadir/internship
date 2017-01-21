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

#include <stdio.h>
#include <maxq1850.h>

#include "sha.h"
#include "shahw_maxq1850.h"


/* Pointer to the start of SHA data memory (shared with the MAA) */
uint8_t *sha_ptr = (uint8_t *)SHA_ADDR;

/* 
 * shahw_maxq1850_checkmode()
 *
 *  Verify that this mode is appropriate for the MAXQ1850 SHA hardware
 *
 */
int8_t shahw_maxq1850_checkmode(uint8_t mode)
{
  int8_t result;
  switch (MODE_MASK(mode)) {
    case MODE_SHA_160:
    case MODE_SHA_224:
    case MODE_SHA_256:
      result = SHA_OK;
      break;

    default:
      result = SHA_ERROR_NOTSUPPORTED;
      break;
  }

  return result;
}


/* 
 * shahw_maxq1850_init()
 *
 *  Initialize the MAXQ1850 SHA hardware 
 *
 */
void shahw_maxq1850_init(void)
{
  int i;

  /* Enable SHA memory mapping */
  SHAC = 0x04; 

  /* Wipe SHA memory contents */
  for (i = 0; i < 0x600; i++) {
    sha_ptr[i] = 0;
  }

  return;
}

/* 
 * shahw_maxq1850_hashmsg()
 *
 *  Initialize the MAXQ1850 SHA hardware 
 *
 */
void shahw_maxq1850_hashmsg(uint8_t *message, uint16_t mode, uint16_t firstblock)
{
  int i;
  uint8_t *sha_msgptr = sha_ptr + 64;

  /* Enable SHA memory mapping */
  SHAC = 0x04; 

  /* Set the proper SHA mode */
  switch (mode) {
    case MODE_SHA_160:
      SHAC |= 0x01;
      break;

    case MODE_SHA_224:
      SHAC |= 0x02;
      break;

    case MODE_SHA_256:
      SHAC |= 0x03;
      break;

    default:
      return;
  }

  
  /* If this is the first block, load the SHA initialization values*/
  if (firstblock) {
    SHAC |= 0x08;
  }

  /* Currently, we only use a single 64 byte (512 bit) message area to hash messages */
  /* The message goes into the hardware "backwards", length first and ending with message[0] */
  for (i = 0; i < 0x40; i++) {
    sha_msgptr[0x3f - i] = message[i];
  }

  /* Begin the hash operation by pointing to 0x8040 */
  SHAP = 0x02;

  /* Wait for SHA operation to complete */
  while (SHAC & 0x20);
  
  /* Clear SHAIF and SHAIN */
  if (firstblock) {
    SHAC &= ~0x88;
  }

  return;
}

/* 
 * shahw_maxq1850_copyhash()
 *
 *  Initialize the MAXQ1850 SHA hardware 
 *
 */
void shahw_maxq1850_copyhash(uint8_t* outpointer, uint16_t mode)
{
  int i;
  uint16_t hashsize;

  switch (mode) {
    case MODE_SHA_160:
      hashsize = 160 / 8;
      break;

    case MODE_SHA_224:
      hashsize = 224 / 8;
      break;

    case MODE_SHA_256:
      hashsize = 256 / 8;
      break;

    default:
      return;
  }

  /* Copy the hash out */
  for (i = 0; i < hashsize; i++) {
    outpointer[i] = sha_ptr[(hashsize-1) - i];
  }

  return;
}
