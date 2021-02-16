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

int main() {

  /* You can choose to use the "DEBUG" option or not, up to you. And you can choose to use this header or not, up to you. 
   * Note that if the header is always printed, your output will not match the reference output.
   */ 
  if (DEBUG) printf("Bits of characters entered       Unsigned int     Signed int       Floating-point (binary)                Floating-point (decimal)\n");

  return 0;
}
