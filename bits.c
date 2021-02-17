/*
 * CSE202 SP21 Bits Program
 * Full Name: 
 * Full Lehigh Email Address: 
 */

/* The following C pre-processor statements allow you to compile with gcc option "-DDEBUG" to selectively 
 * take some particular action, such as printing a header for your output. Passing "-DDEBUG" to gcc defines
 * "DEBUG" such that you can test its value (see "if (DEBUG) {}" statement in main). If you don't like this 
 * whole idea/approach, you can delete this comment, the next three lines, and the "if (DEBUG) {}" statement.
 */
#ifndef DEBUG
#define DEBUG 0
#endif

#include <stdio.h> /* for printf, fprintf, etc. */
#include<ctype.h>
#include<stdlib.h>
#include <string.h>

/* You are required to use the following union typedef. Doing so will prevent compiler warnings
 * when you attempt to access a memory location using a different type than when it was declared,
 * and you won't have to explicitly cast your variable references.
 */
typedef union {
  signed int s;
  unsigned int u;
  float f;
  unsigned char c[sizeof(int)];
} num_t;

int main(int argc, char *argv[]) {

  /* You can choose to use the "DEBUG" option or not, up to you. And you can choose to use this header or not, up to you. 
   * Note that if the header is always printed, your output will not match the reference output.
   */ 
  if (DEBUG) printf("Bits of characters entered       Unsigned int     Signed int       Floating-point (binary)                Floating-point (decimal)\n");

  //check the endian of the running computer
  int see_endian = strcmp(argv[1], "-e"); 

  //0 if the system is small endian, 1 otherwise
  int big_small = 0;
  if(see_endian == 0)
  {
    int n = 1;
    char *c = (char*)&n; 
    if (*c)
    {
      printf("Little endian\n");
    }     
    else
    {
      printf("Big endian\n"); 
      big_small = 1;
    }
    return 0;
  }

  //check if the command line argv[] is a valid hexadecimal string
  for(int i = 0; i<8; i++)
  {
    if( isxdigit(argv[1][i]) )
    {}
	  else
    {
      printf( " The entered input is not a hexadecimal number. \n" );
      return 0;
    }
  }

  //if the argv[] is a valid hex number than proceed to the approach part
  //read command line into 4 character array
  unsigned char hex [4];
  int num = (int)strtol(argv[1], NULL, 16);

  //save the number into 4 character bytes
  if(big_small==0)
  {
    hex[0] = (num >> 24) & 0xFF;
    hex[1] = (num >> 16) & 0xFF;
    hex[2] = (num >> 8) & 0xFF;
    hex[3] = num & 0xFF;
  }
  //if big endian, simply reverse the order of little endian
  else
  {
    hex[3] = (num >> 24) & 0xFF;
    hex[2] = (num >> 16) & 0xFF;
    hex[1] = (num >> 8) & 0xFF;
    hex[0] = num & 0xFF;
  }

  //convert bytes into bits form(binary)
  unsigned char bits[32];
  unsigned char mask = 1; 
  int i = 0;

  for(i = 0; i<8; i++)
  {
    bits[i] = (hex[3] & (mask << i)) != 0;
  } 
  for(i = 8; i<16; i++)
  {
    bits[i] = ((hex[2] << 8) & (mask << i)) != 0;
  } 
  for(i = 16; i<24; i++)
  {
    bits[i] = ((hex[1] << 16) & (mask << i)) != 0;
  } 
  for(i = 24; i<32; i++)
  {
    bits[i] = ((hex[0] << 24) & (mask << i)) != 0;
  } 

  //print out the correct binary representation in reverse due to the saving method
  for(i = 31; i>=0; i--)
  {
    printf("%d", bits[i]);
  }

  //present in the form of integer
  signed int signed_int = (hex[0] << 24) + (hex[1] << 16) + (hex[2] << 8) + hex[3];
  printf("\nSigned Int: %d\n", signed_int);

  unsigned int unsigned_int = (hex[0] << 24) + (hex[1] << 16) + (hex[2] << 8) + hex[3];
  printf("Unsigned Int: %u\n", unsigned_int);
  
  
}
