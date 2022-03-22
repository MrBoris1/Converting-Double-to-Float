#include "bitFields.h"
#include <assert.h>
#include <stdio.h>

int getBit(int bn,unsigned long val) {
	return (1L<<bn & val)>>bn;
}

void setBit(int bn,int new,unsigned long *val) {
	long i = 1L<<bn;
	if(new) *val = (i | *val);
	else *val = (~i &  *val);
}

long getBitFld(int bs,int len,unsigned long val){
	unsigned long new_bs = getBitFldU(bs,len,val);
	int i = getBit(bs,val);
	if(!i){ return new_bs;}
	for(int p = bs; p>=len;p--){
		setBit(p,1,&new_bs);
	}
	if(len>bs){
		for(int p = bs+len; p>=bs;p--){
			setBit(p,1,&new_bs);
		}	
	}
	long int o = new_bs;
	return o;
}

unsigned long getBitFldU(int bs,int len,unsigned long val) {
	int shift = bs-len+1;
	unsigned long int mask = (1L<<len)-1;
	unsigned long int new = (val & (mask<<shift))>>shift;
	return new;
}

void setBitFld(int bs,int len,unsigned long new,unsigned long *val) {
	for(int i=0; i<=len-1; i++){
		setBit(bs-i,getBit((len-1)-i,new),val);
	}
}
