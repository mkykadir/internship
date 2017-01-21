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
#include <string.h>

#include "sha.h"

#include "shahw_maxq1850.h"

#define MAXQ1850

#ifdef SHA160
uint32_t SHA_160_Initial[] = 
{
  0x67452301,
  0xefcdab89,
  0x98badcfe,
  0x10325476,
  0xc3d2e1f0
};
#define SHA_160_INITIAL_LENGTH    5

uint32_t SHA_160_CONSTANTS[] = 
{
  0x5a827999,   // 0 <= t <= 19 
  0x6ed9eba1,   // 20 <= t <= 39 
  0x8f1bbcdc,   // 40 <= t <= 59 
  0xca62c1d6    // 60 <= t <= 79 
};

#endif

#ifdef SHA224
uint32_t SHA_224_Initial[] = 
{
  0xc1059ed8,
  0x367cd507,
  0x3070dd17,
  0xf70e5939,
  0xffc00b31,
  0x68581511,
  0x64f98fa7,
  0xbefa4fa4
};
#define SHA_224_INITIAL_LENGTH    8
#endif

#ifdef SHA256
uint32_t SHA_256_Initial[] = 
{
  0x6a09e667,
  0xbb67ae85,
  0x3c6ef372,
  0xa54ff53a,
  0x510e527f,
  0x9b05688c,
  0x1f83d9ab,
  0x5be0cd19
};
#define SHA_256_INITIAL_LENGTH    8
#endif

#ifdef SHA384
uint64_t SHA_384_Initial[] = 
{
  0xcbbb9d5dc1059ed8ULL,
  0x629a292a367cd507ULL,
  0x9159015a3070dd17ULL,
  0x152fecd8f70e5939ULL,
  0x67332667ffc00b31ULL,
  0x8eb44a8768581511ULL,
  0xdb0c2e0d64f98fa7ULL,
  0x47b5481dbefa4fa4ULL
};
#define SHA_384_INITIAL_LENGTH    8
#endif

#ifdef SHA512
uint64_t SHA_512_Initial[] = 
{
  0x6a09e667f3bcc908ULL,
  0xbb67ae8584caa73bULL,
  0x3c6ef372fe94f82bULL,
  0xa54ff53a5f1d36f1ULL,
  0x510e527fade682d1ULL,
  0x9b05688c2b3e6c1fULL,
  0x1f83d9abfb41bd6bULL,
  0x5be0cd19137e2179ULL
};
#define SHA_512_INITIAL_LENGTH    8
#endif

#if defined(SHA224) | defined(SHA256) | defined(SHA384) | defined(SHA512)
// Note that the constants for 256 are just the upper 32 bits of each of these first 64 longs
uint64_t SHA_CONSTANTS[] =  
{
  0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
  0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
  0xd807aa98a3030242ULL, 0x12835b0145706fbeULL, 0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
  0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
  0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
  0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
  0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
  0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL, 0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
  0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
  0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
  0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
  0xd192e819d6ef5218ULL, 0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
  0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL, 0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
  0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
  0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
  0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
  0xca273eceea26619cULL, 0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
  0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL, 0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
  0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
  0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
};
#endif

uint8_t workbuffer[128];

#if defined(SHA160) | defined(SHA224) | defined(SHA256)
uint32_t a32, b32, c32, d32, e32, f32, g32, h32; // SHA working variables
uint32_t W32[16];                                // SHA message schedule
uint32_t H32[8];                                 // last SHA result variables
#endif
#if defined(SHA384) | defined(SHA512)
uint64_t a64, b64, c64, d64, e64, f64, g64, h64; // SHA working variables
uint64_t W64[16];                                // SHA message schedule
uint64_t H64[8];                                 // last SHA result variables
#endif

// general support function, required in all SHA flavors
uint64_t sha_ch(uint64_t x, uint64_t y, uint64_t z)
{
  return (x & y) ^ ((~x) & z);
}

// general support function, required in all SHA flavors
uint64_t sha_maj(uint64_t x, uint64_t y, uint64_t z)
{
  uint64_t temp = x & y;
  temp ^= (x & z);
  temp ^= (y & z);
  return temp;  //(x & y) ^ (x & z) ^ (y & z);
}

// SHA 224/256
uint32_t sha_rotr_32(uint32_t val, uint16_t r)
{
  val = val & 0xFFFFFFFFL;
  return ((val >> r) | (val << (32 - r))) & 0xFFFFFFFFL;
}

// SHA-160 ONLY!
uint32_t sha_rotl_32(uint32_t val, uint16_t r)
{
  val = val & 0xFFFFFFFFL;
  return ((val << r) | (val >> (32 - r))) & 0xFFFFFFFFL;
}

// SHA 384/512
uint64_t sha_rotr_64(uint64_t val, uint16_t r)
{
  return (val >> r) | (val << (64 - r));
}

// SHA 224/256
uint32_t sha_shr_32(uint32_t val, uint16_t r)
{
  val = val & 0xFFFFFFFFL;
  return val >> r;
}

// SHA 384/512
uint64_t sha_shr_64(uint64_t val, uint16_t r)
{
  return val >> r;
}

// function for SHA-1
uint32_t sha_sha1f(uint32_t x, uint32_t y, uint32_t z, uint16_t functionnumber)
{
  switch(functionnumber & 0x03)
  {
    case 0 : return (uint32_t) sha_ch(x,y,z);
    case 1 : return (uint32_t) (x ^ y ^ z);
    case 2 : return (uint32_t) sha_maj(x,y,z);
    case 3 : return (uint32_t) (x ^ y ^ z);
  }
  return 0;  // should never get here
}

// function for SHA-256/224
uint32_t sha_bigsigma256_0(uint32_t x)
{
  return sha_rotr_32(x,2) ^ sha_rotr_32(x,13) ^ sha_rotr_32(x,22);
}

// function for SHA-256/224
uint32_t sha_bigsigma256_1(uint32_t x)
{
  return sha_rotr_32(x,6) ^ sha_rotr_32(x,11) ^ sha_rotr_32(x,25);
}

// function for SHA-256/224
uint32_t sha_littlesigma256_0(uint32_t x)
{
  return sha_rotr_32(x,7) ^ sha_rotr_32(x,18) ^ sha_shr_32(x,3);
}

// function for SHA-256/224
uint32_t sha_littlesigma256_1(uint32_t x)
{
  return sha_rotr_32(x,17) ^ sha_rotr_32(x,19) ^ sha_shr_32(x,10);
}

// function for SHA-512/384
uint64_t sha_bigsigma512_0(uint64_t x)
{
  return sha_rotr_64(x,28) ^ sha_rotr_64(x,34) ^ sha_rotr_64(x,39);
}

// function for SHA-512/384
uint64_t sha_bigsigma512_1(uint64_t x)
{
  return sha_rotr_64(x,14) ^ sha_rotr_64(x,18) ^ sha_rotr_64(x,41);
}

// function for SHA-512/384
uint64_t sha_littlesigma512_0(uint64_t x)
{
  return sha_rotr_64(x,1) ^ sha_rotr_64(x,8) ^ sha_shr_64(x,7);
}

// function for SHA-512/384
uint64_t sha_littlesigma512_1(uint64_t x)
{
  return sha_rotr_64(x,19) ^ sha_rotr_64(x,61) ^ sha_shr_64(x,6);
}

int8_t sha_checkMode(uint8_t mode)
{
  int8_t result;
  
  switch (mode) {
#ifdef SHA160
  case MODE_SHA_160:
    result = SHA_OK;
    break;
#endif
#ifdef SHA224
  case MODE_SHA_224:
    result = SHA_OK;
    break;
#endif
#ifdef SHA256
  case MODE_SHA_256:
    result = SHA_OK;
    break;
#endif
#ifdef SHA384
  case MODE_SHA_384:
    result = SHA_OK;
    break;
#endif
#ifdef SHA512
  case MODE_SHA_512:
    result = SHA_OK;
    break;
#endif

    default:
      result = SHA_ERROR_NOTSUPPORTED;
      break;
  }

  return result;
}

void sha_copy32(uint32_t* p1, uint32_t* p2, uint16_t length)
{
  while (length > 0)
  {
    *p2++ = *p1++;
    length--;
  }
}

void sha_copy64(uint64_t* p1, uint64_t* p2, uint16_t length)
{
  while (length > 0)
  {
    *p2++ = *p1++;
    length--;
  }
}

void sha_initialize(int mode)
{
  switch(mode)
  {
#ifdef SHA160
    case MODE_SHA_160 : sha_copy32(SHA_160_Initial, H32, SHA_160_INITIAL_LENGTH); 
                        break;
#endif
#ifdef SHA224
    case MODE_SHA_224 : sha_copy32(SHA_224_Initial, H32, SHA_224_INITIAL_LENGTH); 
                        break;
#endif
#ifdef SHA256
    case MODE_SHA_256 : sha_copy32(SHA_256_Initial, H32, SHA_256_INITIAL_LENGTH); 
                        break;
#endif
#ifdef SHA384
    case MODE_SHA_384 : sha_copy64(SHA_384_Initial, H64, SHA_384_INITIAL_LENGTH); 
                        break;
#endif
#ifdef SHA512
    case MODE_SHA_512 : sha_copy64(SHA_512_Initial, H64, SHA_512_INITIAL_LENGTH); 
                        break;
#endif
    default: return;
  }
}

void sha_copyWordsToBytes32(uint32_t* input, uint8_t* output, uint16_t numwords)
{
    uint32_t temp;
    uint16_t i;
    for (i=0;i<numwords;i++)
    {
        temp = *input++;
        *output++ = (uint8_t)(temp >> 24);
        *output++ = (uint8_t)(temp >> 16);
        *output++ = (uint8_t)(temp >> 8);
        *output++ = (uint8_t)(temp);
    }
}

void sha_copyWordsToBytes64(uint64_t* input, uint8_t* output, uint16_t numwords)
{
    uint64_t temp;
    uint16_t i;
    for (i=0;i<numwords;i++)
    {
        temp = *input++;
        *output++ = (uint8_t)(temp >> 56);
        *output++ = (uint8_t)(temp >> 48);
        *output++ = (uint8_t)(temp >> 40);
        *output++ = (uint8_t)(temp >> 32);
        *output++ = (uint8_t)(temp >> 24);
        *output++ = (uint8_t)(temp >> 16);
        *output++ = (uint8_t)(temp >> 8);
        *output++ = (uint8_t)(temp);
    }
}

void sha_writeResult(int mode, uint8_t* outpointer)
{
  uint16_t numwords;

  numwords = 8;
  if (mode == MODE_SHA_160)
    numwords = 5;
  if (mode == MODE_SHA_224)
    numwords = 7;
  if (mode == MODE_SHA_384)
    numwords = 6;

  switch(mode)
  {
#if defined(SHA160) | defined(SHA224) | defined(SHA256)
    case MODE_SHA_160 : 
    case MODE_SHA_224 : 
    case MODE_SHA_256 : sha_copyWordsToBytes32(H32, outpointer, numwords); 
                        break;
#endif
#if defined(SHA384) | defined(SHA512)
    case MODE_SHA_384 : 
    case MODE_SHA_512 : sha_copyWordsToBytes64(H64, outpointer, numwords);  
                        break;
#endif
  }
}


uint64_t sha_getK(int index, int mode, int select)
{
  switch (MODE_MASK(mode))
  {
#ifdef SHA160
    case MODE_SHA_160 : return SHA_160_CONSTANTS[select];
#endif
#if defined(SHA224) | defined(SHA256) | defined(SHA384) | defined(SHA512)
    case MODE_SHA_224 : // same as 256...
    case MODE_SHA_256 : return SHA_CONSTANTS[index] >> 32;
    case MODE_SHA_384 : // same as 512...
    case MODE_SHA_512 : return SHA_CONSTANTS[index];
#endif
  }
  return 0;
}

uint64_t sha_getW(int index, int mode)
{
  uint64_t newW;
  if (index < 16)
  {
#if defined(SHA384) | defined(SHA512)
    if ((MODE_MASK(mode)==MODE_SHA_384) || (MODE_MASK(mode)==MODE_SHA_512))
      return W64[index];
#endif
#if defined(SHA160) | defined(SHA224)| defined(SHA256)
    if ((MODE_MASK(mode)==MODE_SHA_160) || (MODE_MASK(mode)==MODE_SHA_224) || (MODE_MASK(mode)==MODE_SHA_256))
      return W32[index];
#endif
  }
  newW = 0;
  switch (MODE_MASK(mode))
  {
#if defined(SHA160)
    case MODE_SHA_160 : newW = sha_rotl_32(( W32[(index-3) & 0x0f] ^ 
                          W32[(index-8) & 0x0f] ^ W32[(index-14) & 0x0f] ^ 
                          W32[(index-16) & 0x0f] ),1);
                        W32[index & 0x0f] = newW & 0xFFFFFFFFL;  // just in case...
                        break;
#endif
#if defined(SHA224) | defined(SHA256)
    case MODE_SHA_224 : // same as 256...
    case MODE_SHA_256 : newW = sha_littlesigma256_1(W32[(index-2)&0x0f]) + 
                          W32[(index-7)&0x0f] + 
                          sha_littlesigma256_0(W32[(index-15)&0x0f]) + 
                          W32[(index-16)&0x0f];
                        W32[index & 0x0f] = newW & 0xFFFFFFFFL;  // just in case...
                        break;
#endif
#if defined(SHA384) | defined(SHA512)
    case MODE_SHA_384: // same as 512...
    case MODE_SHA_512: newW = sha_littlesigma512_1(W64[(index-2)&0x0f]) + 
                         W64[(index-7)&0x0f] +
                         sha_littlesigma512_0(W64[(index-15)&0x0f]) + 
                         W64[(index-16)&0x0f];
                       // notice no mask here! 64-bit working schedules
                       W64[index & 0x0f] = newW;
                       break;
#endif
  }
  return newW;
}


void sha_prepareSchedule(uint8_t* message, uint16_t mode)
{
  // we need to copy the initial message into the 16 W registers
  uint16_t i,j;
  uint64_t temp;
  uint8_t bytes_per_word = 4;
  if ((MODE_MASK(mode)==MODE_SHA_384) || (MODE_MASK(mode)==MODE_SHA_512))
    bytes_per_word = 8;
  for (i=0;i<16;i++)
  {
    temp = 0;
    for (j=0;j<bytes_per_word;j++)
    {
      temp = temp << 8;
      temp = temp | (*message & 0xffULL);
      message++;
    }
#if defined(SHA384) | defined(SHA512)
    if (bytes_per_word==8)
      W64[i] = temp;
#endif
#if defined(SHA160) | defined(SHA224) | defined(SHA256)
    if (bytes_per_word==4)
      W32[i] = temp;
#endif
  }
}


int8_t sha_hw_checkmode(uint8_t mode)
{
#if defined (MAXQ1850)
  return shahw_maxq1850_checkmode(mode);
#else
  return SHA_ERROR_NOTSUPPORTED;
#endif
}

void sha_hw_init(void)
{
#if defined(MAXQ1850)
  shahw_maxq1850_init();
#endif
}

void sha_hw_hashblock(uint8_t *message, uint16_t mode, uint16_t init)
{
#if defined(MAXQ1850)
  shahw_maxq1850_hashmsg(message, mode, init);
#endif  
}

void sha_hw_copyhash(uint8_t *output, uint16_t mode)
{
#if defined(MAXQ1850)
  shahw_maxq1850_copyhash(output, mode);
#endif
}


void sha_hashblock(uint8_t* message, uint16_t mode)
{
  uint16_t numrounds;
  uint16_t sha1counter = 0;
  uint16_t sha1functionselect = 0;
  uint16_t i;
  uint64_t nodeT1, nodeT2;

  uint64_t Wt, Kt;

  // chunk the original message into the working schedule
  sha_prepareSchedule(message, MODE_MASK(mode));

#if defined(SHA160) | defined(SHA224) | defined(SHA256)
  if ((MODE_MASK(mode)==MODE_SHA_160) || (MODE_MASK(mode)==MODE_SHA_224) || (MODE_MASK(mode)==MODE_SHA_256))
  {
    a32 = H32[0];
    b32 = H32[1];
    c32 = H32[2];
    d32 = H32[3];
    e32 = H32[4];
    f32 = H32[5];
    g32 = H32[6];
    h32 = H32[7];
  }
#endif
#if defined(SHA384) | defined(SHA512)
  if ((MODE_MASK(mode)==MODE_SHA_384) || (MODE_MASK(mode)==MODE_SHA_512))
  {
    a64 = H64[0];
    b64 = H64[1];
    c64 = H64[2];
    d64 = H64[3];
    e64 = H64[4];
    f64 = H64[5];
    g64 = H64[6];
    h64 = H64[7];
  }
#endif
  numrounds = 80;
  if ((MODE_MASK(mode) == MODE_SHA_256) || (MODE_MASK(mode) == MODE_SHA_224))
    numrounds = 64;


  for (i=0;i<numrounds;i++)
  {
    Wt = sha_getW(i, MODE_MASK(mode));
    Kt = sha_getK(i, MODE_MASK(mode), sha1functionselect);
#ifdef SHA160
    if (MODE_MASK(mode)==MODE_SHA_160)
    {
      nodeT1 = (sha_rotl_32(a32,5) + sha_sha1f(b32,c32,d32,sha1functionselect) + e32 + Kt + Wt); // & 0xFFFFFFFFL;
      e32 = d32;
      d32 = c32;
      c32 = sha_rotl_32(b32,30);
      b32 = a32;
      a32 = nodeT1;
    }
#endif
#if defined(SHA224) | defined(SHA256)
    if ((MODE_MASK(mode)==MODE_SHA_256) || (MODE_MASK(mode)==MODE_SHA_224))
    {
      nodeT1 = (h32 + sha_bigsigma256_1(e32) + sha_ch(e32,f32,g32) + Kt + Wt); // & 0xFFFFFFFFL;
      nodeT2 = (sha_bigsigma256_0(a32) + sha_maj(a32,b32,c32)); // & 0xFFFFFFFFL;
      h32 = g32;
      g32 = f32;
      f32 = e32;
      e32 = d32 + nodeT1;
      d32 = c32;
      c32 = b32;
      b32 = a32;
      a32 = nodeT1 + nodeT2;
    }
#endif
#if defined(SHA384) | defined(SHA512)
    if ((MODE_MASK(mode)==MODE_SHA_384) || (MODE_MASK(mode)==MODE_SHA_512))
    {
      nodeT1 = (h64 + sha_bigsigma512_1(e64) + sha_ch(e64,f64,g64) + Kt + Wt);
      nodeT2 = (sha_bigsigma512_0(a64) + sha_maj(a64,b64,c64));
      h64 = g64;
      g64 = f64;
      f64 = e64;
      e64 = d64 + nodeT1;
      d64 = c64;
      c64 = b64;
      b64 = a64;
      a64 = nodeT1 + nodeT2;
    }
#endif

    sha1counter++;
    if (sha1counter==20)
    {
      sha1functionselect++;
      sha1counter = 0;
    }			

  }

  // now fix up our H array
#if defined(SHA160) | defined(SHA224) | defined(SHA256)
  if ((MODE_MASK(mode)==MODE_SHA_160) || (MODE_MASK(mode)==MODE_SHA_224) || (MODE_MASK(mode)==MODE_SHA_256))
  {
    H32[0] += a32;
    H32[1] += b32;
    H32[2] += c32;
    H32[3] += d32;
    H32[4] += e32;
    H32[5] += f32;
    H32[6] += g32;
    H32[7] += h32;
  }
#endif
#if defined(SHA384) | defined(SHA512)
  if ((MODE_MASK(mode)==MODE_SHA_384) || (MODE_MASK(mode)==MODE_SHA_512))
  {
    H64[0] += a64;
    H64[1] += b64;
    H64[2] += c64;
    H64[3] += d64;
    H64[4] += e64;
    H64[5] += f64;
    H64[6] += g64;
    H64[7] += h64;
  }
#endif
}

int16_t sha_createHash(uint8_t* message, uint16_t length, uint8_t* output, 
		   uint8_t mode)
{
  uint16_t bytes_per_block;
  uint16_t nonpaddedlength;
  uint16_t numblocks;
  uint16_t i,j;
  uint32_t bitlength;
  uint16_t markerwritten;

  uint16_t wordsize = 32;

  if (mode & MODE_HW_ACCEL) {
    if (sha_hw_checkmode(MODE_MASK(mode)) != SHA_OK) {
      return SHA_ERROR_NOTSUPPORTED;
    }
  } else {
    if (sha_checkMode(MODE_MASK(mode)) != SHA_OK) {
      return SHA_ERROR_NOTSUPPORTED;
    }
  }

  if ((MODE_MASK(mode)==MODE_SHA_384) || (MODE_MASK(mode)==MODE_SHA_512)) {
    wordsize = 64;
  }

  // if wordsize is 32 bits, we need 512 bit blocks.  else 1024 bit blocks.
  // that means 16 words are in one message.
  bytes_per_block = 16 * (wordsize / 8);
  // 1 byte for the '80' that follows the message, 8 or 16 bytes of length
  nonpaddedlength = length + 1 + (wordsize/4);
  numblocks = nonpaddedlength / bytes_per_block;
  if ((nonpaddedlength % bytes_per_block)!=0) {
    // then there is some remainder we need to pad
    numblocks++;
  }

  if (mode & MODE_HW_ACCEL) {
    sha_hw_init();
  } else {
    sha_initialize(MODE_MASK(mode));
  }

  bitlength = 8 * length;
  markerwritten = 0;
  // 'length' is our number of bytes remaining.
  for (i=0;i<numblocks;i++)
  {
    if (length > bytes_per_block)
    {
      memcpy(workbuffer, message, bytes_per_block);
      length -= bytes_per_block;
    }
    else if (length==bytes_per_block)
    {
      memcpy(workbuffer, message, length);
      length = 0;
    }
    else // length is less than number of bytes in a block
    {
      memcpy(workbuffer, message, length);
      // message is now used for temporary space
      message = workbuffer + length;     
      if (markerwritten == 0)
      {
        *message++ = 0x80;
        length++;
      }
      while (length < bytes_per_block)
      {
        // this loop is inserting padding, in this case all zeroes
        *message++ = 0;
        length++;
      }
      length = 0;
      // signify that we have already written the 80h
      markerwritten = 1;
    }

    // on the last block, put the bit length at the very end
    if (i == (numblocks - 1))
    {
      // point at the last byte in the block
      message = workbuffer + bytes_per_block - 1;
      for (j=0;j<wordsize/4;j++)
      {
        *message-- = (uint8_t)bitlength;
        bitlength = bitlength >> 8;
      }
    }
    
    if (mode & MODE_HW_ACCEL) {
      /* SHA acceleration in hardware */
      sha_hw_hashblock(workbuffer, MODE_MASK(mode), (i > 0) ? 0 : 1);
    } else {
      /* SHA in software */
      sha_hashblock(workbuffer, MODE_MASK(mode));
    }
    message += bytes_per_block;
  }
  if (mode & MODE_HW_ACCEL) {
    sha_hw_copyhash(output, MODE_MASK(mode));
  } else {
    sha_writeResult(MODE_MASK(mode), output);
  }

  return SHA_OK;
}

/* 
 * This function will take a singly linked list of messages fragments and
 *  compute the SHA message digest over the concatenated result.
 *
 */
int16_t sha_createHash_multi(sha_msg_frags *frags, uint8_t* output, uint8_t mode)
{
  uint16_t bytes_per_block;
  uint16_t j;
  uint32_t bitlength;
  uint16_t wordsize;
  uint16_t frags_done;
  uint32_t totalbytes;
  uint16_t fragbytes;
  uint16_t wantbytes;
  uint16_t firstblock;

  uint8_t *workptr;
  sha_msg_frags *current_frag;
  uint8_t *fragptr;

  /* Point to the first message fragment */
  if (frags != NULL) {
    current_frag = frags;
  }

  /* Check the mode */
  if (mode & MODE_HW_ACCEL) {
    if (sha_hw_checkmode(MODE_MASK(mode)) != SHA_OK) {
      return SHA_ERROR_NOTSUPPORTED;
    }
  } else {
    if (sha_checkMode(MODE_MASK(mode)) != SHA_OK) {
      return SHA_ERROR_NOTSUPPORTED;
    }
  }

  /* Fix the wordsize */
  if ((MODE_MASK(mode)==MODE_SHA_384) || (MODE_MASK(mode)==MODE_SHA_512)) {
    wordsize = 64;
  } else {
    wordsize = 32;
  }

  // if wordsize is 32 bits, we need 512 bit blocks.  else 1024 bit blocks.
  // that means 16 words are in one message.
  bytes_per_block = 16 * (wordsize / 8);

  if (mode & MODE_HW_ACCEL) {
    sha_hw_init();
  } else {
    sha_initialize(MODE_MASK(mode));
  }

  firstblock = 1;
  totalbytes = 0;
  frags_done = 0;
  fragptr = current_frag->message;
  workptr = workbuffer;
  memset(workbuffer, 0, bytes_per_block);
  while (!frags_done) {
    
    /* Attempt to fill the workbuffer with bytes_per_block */
    while (workptr - workbuffer < bytes_per_block) {
      /* How many bytes are in the current frag? */
      fragbytes = current_frag->length - (fragptr - current_frag->message);
      wantbytes = bytes_per_block - (workptr - workbuffer);
      /* Compare that to how many we need */
      if (fragbytes > wantbytes) {
	/* Simply copy the bytes in and increment the pointers */
	memcpy(workptr, fragptr, wantbytes);
	workptr += wantbytes;
	fragptr += wantbytes;
	totalbytes += wantbytes;
      } else {
	/* Copy as much in as we can, and switch to a new frag */
	memcpy(workptr, fragptr, fragbytes);
	workptr += fragbytes;
	fragptr += fragbytes;
	totalbytes += fragbytes;
	if (current_frag->next_frag != NULL) {
	  current_frag = current_frag->next_frag;
	  fragptr = current_frag->message;
	} else {
	  /* No more frags. End of message */
	  break;
	}
      }
    }

    /* Check for last block */
    if (workptr - workbuffer < bytes_per_block) {
      /* Empty or partial last block. Last block to hash */
      frags_done = 1;
      /* Tag the work buffer with 0x80, pad, and length */
      *workptr++ = 0x80;
      /* Figure out if we have space to insert the length */
      if (workptr - workbuffer > bytes_per_block - 8) {
	/* Nope. Hash this block and go around for size */
	if (mode & MODE_HW_ACCEL) {
	  /* SHA acceleration in hardware */
	  sha_hw_hashblock(workbuffer, MODE_MASK(mode), firstblock);
	} else {
	  /* SHA in software */
	  sha_hashblock(workbuffer, MODE_MASK(mode));
	}
	firstblock = 0;
	memset(workbuffer, 0, bytes_per_block);
	workptr = workbuffer;
      }

      /* Plug in the size at the end of this block */
      workptr = workbuffer + bytes_per_block - 1;
      totalbytes *= 8;
      for (j = 0; j < wordsize / 4; j++) {
	*workptr-- = totalbytes & 0xff;
	totalbytes >>= 8;
      }
    }

    /* Hash the block */
    if (mode & MODE_HW_ACCEL) {
      /* SHA acceleration in hardware */
      sha_hw_hashblock(workbuffer, MODE_MASK(mode), firstblock);
    } else {
      /* SHA in software */
      sha_hashblock(workbuffer, MODE_MASK(mode));
    }
  
    /* Reset for the next round */
    firstblock = 0;
    memset(workbuffer, 0, bytes_per_block);
    workptr = workbuffer;
  }

  /* Copy the message digest to user's buffer */
  if (mode & MODE_HW_ACCEL) {
    sha_hw_copyhash(output, MODE_MASK(mode));
  } else {
    sha_writeResult(MODE_MASK(mode), output);
  }
  
  return SHA_OK;
}
