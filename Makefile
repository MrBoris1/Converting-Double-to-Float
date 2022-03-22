CC = gcc
CFLAGS = -Wall -std=c18 -ggdb

test : testFloatx
	./testFloatx 16 4
	
gdb : testFloatx
	gdb -ex "break doubleToFloatx" -ex "run 16 4" testFloatx
	
testFloatx : testFloatx.c floatx.c floatx.h bitFields.c bitFields.h	
	$(CC) $(CFLAGS) -o testFloatx  testFloatx.c floatx.c bitFields.c -lm

testBits : testBitFields 
	./testBitFields
	
bfgdb : testBitFields
	gdb testBitFields
	
testBitFields : testBitFields.c bitFields.c bitFields.h	
	$(CC) $(CFLAGS) -o testBitFields  testBitFields.c bitFields.c
	
clean :
	-rm testBitFields testFloatx