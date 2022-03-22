# Extending Floating Point Numbers

## Introduction

We use the internal representation of IEEE floating point numbers (float and double) in programs such as C and C++. We know the IEEE standard to represent floating point numbers in 32 or 64 bits worth of data. Some applications need the flexibility of floating point numbers, but may not need the full precision offered by the standard float (32 bit) or double (64 bit) implementations of floating point numbers. Or, applications may need higher precision, and are willing to sacrifice the range by decreasing the number of exponent bits. This project asks you implement a generalized floating point number capability – one which uses an arbitrary total number of bits, broken into a sign bit, an arbitrary number of exponent bits, and an arbitrary number of fraction bits to represent a floating point number.  We will call this generalized floating point number a “floatx” number. 

Other than changing the number of bits for the sub-fields, all the rest of the IEEE conventions for floating point numbers must be followed:
- The left-most (most significant) bit is a sign bit – 0 for positive, 1 for negative
- The next expBits bits represent an exponent field, biased by 2<sup>(expBits-1)</sup> – 1
- Exponent bits of all ones represents special values like infinity (if fraction bits are all zero), or “Not a Number” (Nan) (if fraction bits are not all zero.)
- The remaining bits represent a fraction field, “F”.  For most numbers, there is an implied “1.” in front of the fraction so we interpret it as “1.F”.  
- If the exponent field and the fraction field are all zeroes, that represents the number 0.0.
- If the exponent field is all zeroes, but the fraction field is not zero, then we treat the number as a “sub-normal” (or denormalized) number, and assume it has the value of 0.F x 2<sup>-bias</sup>

Obviously, creating a floatx number will require a lot of bit manipulation. In order to organize the bit manipulation, I have provided suggestions for a library of bit manipulation functions that allow you to extract and insert individual bits and fields of bits into and out of a long integer. However, I have not provided complete implementations of these libraries. You are not required to use these libraries, but I would recommend completing the libraries and using them. Whether you use the libraries or not, you still have to perform the bit manipulation, and I found that using these libraries made the project much easier to understand.

We will use the standard double-precision floating point specification to provide values to convert to the floatx format. The Wikipedia [Double-precision floating-point](https://en.wikipedia.org/wiki/Double-precision_floating-point_format) article does a good job of describing this format. For the project, you will need to implement a single function, the `doubleToFloatx` function that takes a double precision floating point input argument, along with the total number of bits and the number of exponent bits for the floatx version of the value. The function needs to return the floatx version of the number. We define a floatx number as a 64 bit unsigned integer (an unsigned long). However, we will only be using the rightmost bits (bit positions totBits-1 to zero) for our floatx value.

## Provided to in the Repositorie

The repository already contains the infrastructure, as follows:

### bitFields.h and bitFields.c

These files are the bit-twiddling library that you will find useful for the program. The bitFields.h file declares five functions whose definitions appear in bitFields.c. These functions include a get and set function for a single bit, as well as get and set functions for bit fields that contain multiple bits. The get bit field function has two different flavors - the standard `getBitFld` function returns a signed value with the sign bit of the sub-field propagated. The `getBitFldU` function returns an unsigned version of the bit field, that is padded on the left with zeros.

### testBitFields.c

This is some code that is provided for you to unit test the bitFields functions. It uses the functions in the way they were intended, and prints results based on that usage.

### floatx.h and floatx.c

The floatx.h file declares the single floatx function, `doubleToFloatx`, we will be working on for this project. The floatx.h file also contains a typedef statement to define floatx as an unsigned long (64 bit) integer. 

### testFloatx.c

This is a program that uses command line arguments to specify 1) the total number of bits, and 2) the number of exponent bits in a floatx format. It then reads standard input, looking for a double precision floating point value. For each floating point value found in standard input, the testFloatx program invokes the `doubleToFloatx` with the value read from standard input, and the total bits and exponent size specified in the command line arguments. Then the testFloatx program prints the original value, the floatx specification, and the floatx value in hexadecimal. Any non-whitespace characters from standard input that cannot be translated to a double will cause the program to stop.

### test1.txt

A text file which contains some example floating point values to test with. You can use redirection, running a command like `./testFloatx 32 8 <test1.txt` to see how all the values in test1.txt would be represented in floatx with 32 bits and 8 exponent bits.

### Makefile

I have provided a Makefile with several targets:

- `clean` Removes all the files Makefile can create
- `testBitFields` - creates the testBitFields executable from testBitFields.c and bitFields.c 
- `bfgdb` - A target to run gdb on the testBitFields executable 
- `testFloatx` - creates the testFloatx executable from testFloatx.c, floatx.c, and bitFields.c. 
- `gdb` - A target to run gdb on the testFloatx executable. This will automatically set a breakpoint at the first instruciton in `doubleToFloatx`, and run with command line arguments 16 and 4. You will still need to type in values to convert on stdin, which is the keybaord in this case.
- `test` - Runs the testFloatx code with total bits of 16, of which 4 are exponent bits. You will still need to type values to convert. Type something like "q" and hit enter to quit.

Here is an example of the output produced when the program runs:

```
>cat test1.txt
1.0
100.0
1.3333333333333333333333333333
1.27563e45
6.23e22
7.9e-39
3.4028235e+38
3.4028236e+38
q
>./testFloatx 32 8 <test1.txt
             1 = floatx(32,8) : 000000003f800000
           100 = floatx(32,8) : 0000000042c80000
     1.3333333 = floatx(32,8) : 000000003faaaaaa
   1.27563e+45 = floatx(32,8) : 000000007f800000
      6.23e+22 = floatx(32,8) : 00000000655314a2
       7.9e-39 = floatx(32,8) : 00000000002c0bf8
 3.4028235e+38 = floatx(32,8) : 000000007f7fffff
 3.4028236e+38 = floatx(32,8) : 000000007f7fffff
Input : q not recognized as a double...         quitting
