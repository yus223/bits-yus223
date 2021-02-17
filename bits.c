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
  num_t hex;
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
      printf( "Invalid input\n" );
      return 0;
    }
  }

  //if the argv[] is a valid hex number than proceed to the approach part
  //read command line into 4 character array
  int num = (int)strtol(argv[1], NULL, 16);

  //save the number into 4 character bytes
  if(big_small==0)
  {
    hex.c[0] = (num >> 24) & 0xFF;
    hex.c[1] = (num >> 16) & 0xFF;
    hex.c[2] = (num >> 8) & 0xFF;
    hex.c[3] = num & 0xFF;
  }
  //if big endian, simply reverse the order of little endian
  else
  {
    hex.c[3] = (num >> 24) & 0xFF;
    hex.c[2] = (num >> 16) & 0xFF;
    hex.c[1] = (num >> 8) & 0xFF;
    hex.c[0] = num & 0xFF;
  }

  //convert bytes into bits form(binary)
  unsigned char bits[32];
  unsigned char mask = 1; 
  int i = 0;

  for(i = 0; i<8; i++)
  {
    bits[i] = (hex.c[3] & (mask << i)) != 0;
  } 
  for(i = 8; i<16; i++)
  {
    bits[i] = ((hex.c[2] << 8) & (mask << i)) != 0;
  } 
  for(i = 16; i<24; i++)
  {
    bits[i] = ((hex.c[1] << 16) & (mask << i)) != 0;
  } 
  for(i = 24; i<32; i++)
  {
    bits[i] = ((hex.c[0] << 24) & (mask << i)) != 0;
  } 

  //print out the correct binary representation in reverse due to the saving method
  for(i = 31; i>=0; i--)
  {
    printf("%d", bits[i]);
  }
  printf("     ");

  //present in the form of integer
  hex.s = (hex.c[0] << 24) + (hex.c[1] << 16) + (hex.c[2] << 8) + hex.c[3];

  //change the integer to an unsigned int because they have the same magnitude
  hex.u = hex.s + UINT32_MAX+1;
  printf("%-15u", hex.u);
  printf("%-15d", hex.s);

  //print in floating point form
  int exponent = 0; int times = 7; long double single_bit = 1; char sign ='a';
  //find the sign
  if(bits[31]==0)
  {
    sign = '+';
  }
  else
  {
    sign = '-';
  }
  //find the exponent
  for(i = 30; i>22; i--)
  {
    if(times==0)
    {
      if(bits[i]==1)
      {
        exponent += 1;
      }
      break;
    }
    for(int j = times; j > 0; j--)
    {
      single_bit *= bits[i] * 2;
    }
    exponent += single_bit;
    single_bit = 1;
    times--;
  }
  //denormalized case
  if(exponent == 0)
  {
    printf("%c",sign);
    printf("0.");
    for(i = 22; i>=0; i--)
    {
      printf("%d", bits[i]);
    }
    printf("x2^-01111110     ");
  }

  int jump = 0;
  //normalized case
  if(exponent < 255 && exponent >=1)
  {
    char bits2[7]; int binary_e = 0; char sign2 ='a';
    if(exponent-127 != 0)
    {
      printf("%c",sign);
      printf("1.");
      for(i = 22; i>=0; i--)
      {
        printf("%d", bits[i]);
      }
      if(exponent<127)
      {
        binary_e = 127 - exponent;
        sign2 = '-';
      }
      else
      { 
        binary_e = exponent-127;
        sign2 = '+';
      }
      for(i=0;binary_e>0;i++)    
      { 
        bits2[i]=binary_e%2;    
        binary_e=binary_e/2;    
      }  
      printf("x2^%c", sign2);
      if(exponent==128)
      {
        printf("00000001     ");
      }
      else
      {
        for(i=7;i>=0;i--)
        {
          printf("%d",bits2[i]);
        }
      }
      printf("     ");
    }
    else
    {
      printf("%c",sign);
      printf("1.");
      for(i = 22; i>=0; i--)
      {
        printf("%d", bits[i]);
      }
      printf("x2^+00000000     ");
    }
  }
  //special case

  else if(exponent == 255)
  {
    for(i = 22; i>=0; i--)
    {
      if(bits[i]==1)
      {
        printf("%-10s", "NaN");
        jump = 1;
        break;
      }
    }
    if(jump == 0)
    {
      printf("%-10c%s", sign, "Inf");
    }
  }

  //change the bytes to float
  printf("%+g\n", hex.f);
  return 0;
}
