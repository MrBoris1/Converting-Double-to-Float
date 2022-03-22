#include "floatx.h"
#include "bitFields.h"
#include <stdio.h> 
#include <assert.h>
#include <limits.h> // for CHAR_BIT - number of bits per byte
#include <math.h> // for isinf and isnan

union hexDouble {
   	double dbl;
   	long lng;
} unionVal;

floatx doubleToFloatx(double val,int totBits,int expBits) {
	unionVal.dbl = val;
	unsigned long sign=getBitFldU(63,1,unionVal.lng);
	floatx total = 0; 

	if(getBitFldU(62,11,unionVal.lng) == ((1L<<11)-1) && getBitFld(51,52,unionVal.lng) == 0) {setBitFld(totBits-2,expBits,(1L<<expBits)-1,&total); return total; }
	if(getBitFldU(62,11,unionVal.lng) == ((1L<<11)-1) && getBitFld(51,52,unionVal.lng) != 0) {setBitFld(totBits-2,expBits+1,(1L<<(expBits+1))-1,&total); return total; }

	unsigned long expo = getBitFldU(62,11,unionVal.lng);
	expo = expo - (1<<10) + (1<<(expBits-1));
	unsigned long new_expo=expo;
	if (new_expo >= pow(2,expBits)-1) {setBitFld(totBits-2,expBits,pow(2,expBits)-1,&total); return total; }

	unsigned long frac = getBitFldU(51,totBits-expBits-1,unionVal.lng);
	
	setBitFld(1,1,sign,&total);
	setBitFld(totBits-2,expBits,expo,&total);
	setBitFld(totBits-expBits-2,totBits-expBits-1,frac,&total);
	return total;
}