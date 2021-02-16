# CSE202-Bits-SP2021
Bits: A programming exercies to store, access and "play around" with bits and bytes in memory

# Learning Objectives
1) Understand how multi-byte data objects are either stored in Little Endian or Big Endian form
2) Understand how to access mult-byte objects as various data types through the use of a union typedef
3) Understand how to use bit-wise operators of &, |, <<, and >>
4) Understand signed and unsigned integers do not differ in memory, only in interpretation
5) Understand the encoding of the floating-point format
6) Learn how to use git and create a virtual Unix environment (if student chooses to code on a Windows machine)

# Instructions
Write a C program named bits.c to accept 8 hex characters (most significant on the left), store them in 4 adjacent bytes in memory, and access and print out the equivalent of the binary bits, the value when interpreted as an unsigned int, the value when interpreted as a signed int, the value when interpreted as a floating-point number (significand x 2^exponent), and the value when interpreted as a float (using %+g). Here's an example.

$> a.out 3fc00000  
00111111110000000000000000000000 &nbsp; &nbsp; &nbsp;&nbsp;1069547520 &nbsp; &nbsp; &nbsp;&nbsp;1069547520 +1.10000000000000000000000x2^+00000000 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;+1.5

If you pass "-e" as an argument, the Endianness of the machine is printed out. Here's an example when run on a sunlab computer, which stores its bytes in Little Endian format. If your program is compiled and run on a computer which stores its bytes in Big Endian format, the output should be "Big Endian".

$> a.out -e  
Little Endian

Lastly, if you input anything other than 8 hex characters (adjacent to one another), the program exits with an error message. Here's an example.

$> a.out Homie  
Invalid input

# Approach
1) After verifying the input is valid, read the input 8 hex characters into the union's 4 character array. You will have to be mindful of the "Endianness" of the system you are compiling and running on as you want to be able to access those same 4 bytes of the character array as a unsigned int, signed int, or float and have the bytes in the right order when doing so.
2) After (or while) storing the hex digits, you will need to print out the bits of each byte.
3) Print out the 4 bytes at the address of the union variable as an unsigned int and a signed int.
4) Decode the 4 bytes at the address of the union variable into the various fields of the float representation and print to match the format of the reference output's "Floating-point (binary)".
5) Print out the 4 bytes at the address of the union variable as a floating-point value in decimal using "%+g". You may choose to place a width specifier before the "g" to yield any desired spacing.

# Important Notes
1) The case of the input hex characters can be uppercase, lowercase, or mixed case.
2) You must write your code to support running on a Little Endian computer and a Big Endian computer.
3) You can place as many or as few whitespace characters between your output fields as whitespace will be ignored when comparing your program's output with the reference output.
4) You can use any case for any letters in your output as the case of the letters are ignored when comparing your program's output with the reference output.
5) If you compile with "gcc -DDEBUG bits.c", you can define DEBUG (give it a nonzero value) such that you can take some particular action, such as printing a header as show in the output below. The bits.c file you are given has this ability, and the bits.gold reference executable was compiled this way, for your convenience. You are welcome to NOT use the "debug" code/methodology. Here's an example of the output from bits.gold. Note the formatting is a bit off here, but when printed using a fixed-width font, the column headers and fields line up.

$> bits.gold 00000000  
Bits of characters entered &nbsp; &nbsp; &nbsp;&nbsp;Unsigned int &nbsp; &nbsp;&nbsp;Signed int &nbsp; &nbsp; &nbsp;&nbsp;Floating-point (binary) &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;Floating-point (decimal)  
00000000000000000000000000000000 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;0 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;0 +0.00000000000000000000000x2^-01111110 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;+0

6) You MUST use the union typedef provided in the bits.c starter file.
7) You are NOT allowed to use any library functions or other programs to directly print the bits of a byte OR to load the hex input values into the union's character array OR to print out the fields of a floating-point value... use &, |, <<, or >>.
8) Do NOT modify the makefile, tests.in, tests.goldBE, tests.goldLE, or runTests.sh files... only modify the bits.c file.
9) You may wish to use the site https://www.h-schmidt.net/FloatConverter/IEEE754.html to help you determine/verify floating-point bits and values.
10) Refer to the Programming Assignment Grading Rubric on Coursesite to maximize your score.
11) To submit your code for grading, simply perform a "git push"; which will upload your changes to GitHub Classroom and run the auto-grader. You may continue to push changes until you are informed "All tests passed" or the deadline published on Coursesite.
12) Post any questions on Piazza.
