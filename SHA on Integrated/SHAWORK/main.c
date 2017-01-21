/*
  This code finished in 26.08.2016
  by Muhammed Kadir Yücel
  at Belbim Internship in Istanbul World Trade Center

  SHA generator function and other MAXQ1850 related standart functions are licensed for Maxim Integrated Products Incorporated. 


*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sha.h"
#include <stdint.h>
#include "serial.h"
#include <MAXQ1850.h>
#include <string.h>

void hexdump(uint8_t *b, uint8_t len);                      //function that prints values in hex format
void myRandom(char*);                                       //function that generates random length random strings
int checkHashPattern(const uint8_t*, uint8_t*, uint8_t);    //function that checks hash is ok for given pattern

void main(void)
{
  int status;
  char randomStr[32];
  uint8_t getByteArray[105];
  uint8_t totalString[200];
  int i = 0;
  uint8_t patternSize;

  uint8_t SHA256_DIGEST_LEN = 32; //length for hash output
  uint8_t SHA_256_EX_1_LEN; //length for string that will be hashed
  uint8_t SHA_256_EX_1_M[100];  //array for data input
  uint8_t sha_output[32];  //array to hold generated hash output
  uint16_t mySeed;          //integer to hold random generated number
  uint8_t patternArray[100]; //array that holds pattern
  uint8_t arraySize; //holds size of getByteArray
  uint8_t strSize;  //holds data length got from getByteArray
  uint8_t hwAccel;  //if 0x01 enable hw acceleration, else if 0x02 disable hw acceleration

  //indexes for for loops
  int index;
  int myindex;

  while((PMR&0x40) == 0) {};                          //wait for hardware engine
  mySeed = RNR;                                       //generates random number
  srand(mySeed);                                      //seed for rand() function      

  serial_init();                                      //intializes printf and scanf functions for MAXQ1850's serial port

  while(1)
  {
    getByteArray[0] = getchar();
    if(getByteArray[0] == 0x02)
    {
      getByteArray[1] = getchar();
      arraySize = getByteArray[1];
      strSize = arraySize-5;
      getByteArray[2] = getchar();
      getByteArray[3] = getchar();
      for(myindex = 0; myindex < strSize; myindex++)
      {
        getByteArray[myindex + 4] = getchar();
      }
      getByteArray[arraySize-1] = getchar();
      if(!getByteArray[arraySize-1] == 0x03) return;
      
      hwAccel = getByteArray[2];
      patternSize = getByteArray[3];
      for(index = 0; index < patternSize; index++)
      {
        patternArray[index] = getByteArray[index+4];
      }

      for(index = 0; index < strSize; index++)
      {
        SHA_256_EX_1_M[index] = getByteArray[index+patternSize+4];
      }
      SHA_256_EX_1_M[index] = '\0';
    }else
    {
      return;
    }
    strcpy(totalString,  SHA_256_EX_1_M);
    SHA_256_EX_1_LEN = strlen(totalString);
    if(hwAccel == 0x01)
    {
      sha_createHash(totalString, SHA_256_EX_1_LEN, sha_output, MODE_SHA_256|MODE_HW_ACCEL);
    }else if(hwAccel == 0x02)
    {
      sha_createHash(totalString, SHA_256_EX_1_LEN, sha_output, MODE_SHA_256);
    }

    while(checkHashPattern(sha_output, patternArray, patternSize) == 0) //loop while until sha is ok for given pattern
    {
      myRandom(randomStr);
      strcpy(totalString, SHA_256_EX_1_M); //copy given data into total string
      strcat(totalString, randomStr);     //copy random string into total string
      SHA_256_EX_1_LEN = strlen(totalString); //get length of the total string
      sha_createHash(totalString, SHA_256_EX_1_LEN, sha_output, MODE_SHA_256|MODE_HW_ACCEL);    //standart function that generates SHA-256 hashes
      printf("\r\n\r\nTotal string: %s\r\n", totalString); //print total string
      hexdump(sha_output, SHA256_DIGEST_LEN); //print generated hash in hex format
      printf("\r\ncount: %d\r\n", i); //print current step count
      i++;
    }
  }
}

void hexdump(uint8_t *b, uint8_t len)
{
  int i;

  for (i=0;i<len;i++)
  {
    printf("%02x", b[i]);
  }
} 

void myRandom(char *arr)            //this function generates random characters and adds them into char array that's length is also random
{                       
    uint8_t randomSize;
    uint8_t in;
    randomSize = rand() % 31 + 1;  // 1 ile 31 arasýnda random sayý oluþtur
    for(in = 0; in < randomSize; in++){
        arr[in] = '!' + rand() % 94;
    }
    arr[randomSize] = '\0';
}

int checkHashPattern(const uint8_t* input, uint8_t* pattern, uint8_t patternsize)    //this function checks compliance of hash and pattern
{
  int index;
  for(index = 0; index < patternsize; index++)
  {
    if(input[index] != pattern[index])
    {
      return 0;
    }
  }

  return 1;
}


