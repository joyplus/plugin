#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "joyplus_des.h"

/*void Log(char* log){
   __android_log_print(ANDROID_LOG_INFO, "JNIMsg", log);
}
void LogNumber(char* log,int len){
   int i=0;
   for(i=0;i<len;i++) *(log+i) =  *(log+i)+48;
   __android_log_print(ANDROID_LOG_INFO, "JNIMsg", log);
}*/
void  LOGBIT(char* data,int len){
      char* msg = malloc(len+1);
      memset(msg,0,len+1);
      memcpy(msg,data,len);
	  int i=0;
      for(i=0;i<len;i++){
            *(msg+i) +=48;
	  }	  
     LOGD("Jas","%s",msg);
}
void LOGSTR(char* data,int len){
      char* msg = malloc(len+1);
      memset(msg,0,len+1);
      memcpy(msg,data,len);
     LOGD("Jas","%s",msg);
}
void  sBoxPermute(char* ExpandByte,char* SBoxByte){
    const   int s1[4][16] = {
                { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
                { 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
                { 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
                { 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 } };

        /* Table - s2 */
    const   int s2[4][16] = {
                { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
                { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
                { 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
                { 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 } };

        /* Table - s3 */
    const   int s3[4][16] = {
                { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
                { 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
                { 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
                { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 } };
        /* Table - s4 */
    const   int s4[4][16] = {
                { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
                { 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
                { 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
                { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 } };

        /* Table - s5 */
    const   int s5[4][16] = {
                { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
                { 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
                { 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
                { 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 } };

        /* Table - s6 */
    const   int s6[4][16] = {
                { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
                { 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
                { 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
                { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 } };

        /* Table - s7 */
    const   int s7[4][16] = {
                { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
                { 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
                { 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
                { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 } };

        /* Table - s8 */
    const   int s8[4][16] = {
                { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
                { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
                { 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
                { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };
     char* sBoxByte = malloc(32);
     memset(sBoxByte,0,32);
     int binary   = 0;
     int m,i,j,k;
     for (m = 0; m < 8; m++) {
        i = 0; j = 0;
        i = ((*(ExpandByte+m*6+0))*2)+ (*(ExpandByte+m*6+5));
        j = ((*(ExpandByte+m*6+1))*2*2*2)+((*(ExpandByte+m*6+2))*2
                *2) + ((*(ExpandByte+m*6+3))*2) + (*(ExpandByte+m*6+4));
        switch (m) {
            case 0:
                binary = s1[i][j];
                break;
            case 1:
                binary = s2[i][j];
                break;
            case 2:
                binary = s3[i][j];
                break;
            case 3:
                binary = s4[i][j];
                break;
            case 4:
                binary = s5[i][j];
                break;
            case 5:
                binary = s6[i][j];
                break;
            case 6:
                binary = s7[i][j];
                break;
            case 7:
                binary = s8[i][j];
                break;
        }
        for(k=0;k<4;k++){
            *(sBoxByte+m*4+k) = ((binary&0x0008)==0x0008);
            binary = binary<<1;
        }
     }
     memcpy(SBoxByte,sBoxByte,32);
     free(sBoxByte);
}

//void StrToHex(char* str);
void generateKeys(char* decodeKey,char* Keys){
     char* key  = malloc(56);
     memset(key,0,56);
     char* tempKey = malloc(48);
     memset(tempKey,0,48);
     char* keys = malloc(16*48);
     memset(keys,0,16*48);
     char* Loop = {"1122222212222221"};
     int  i,j,k,tempLeft,tempRight;
     for (i = 0;i <7;i++) {
        for(j = 0, k = 7; j < 8; j++, k--) {
            *(key+8*i+j) = *(decodeKey+8*k+i);
        }
    } 
	// LOGD("Jas","generateKeys  Key=--->");
 //  LOGBIT(key, 56);
   
    for(i=0;i<16;i++){
        tempLeft  = 0;
        tempRight = 0;
        for (j = 0; j < (*(Loop+i)-48); j++) {
            tempLeft  = *key;
            tempRight = *(key+28);
            for ( k = 0; k <27; k++) {
                *(key+k) = *(key+k+1);
                *(key+28+k) = *(key+29+k);
            }
            *(key+27) = tempLeft;
            *(key+55) = tempRight;
        }
	// LOGD("Jas","generateKeys %d Key=--->",i);
    //   LOGBIT(key, 56);
        memset(tempKey,0,48);
        *tempKey         = *(key+13);
        *(tempKey+1)  = *(key+16);
        *(tempKey+2)  = *(key+10);
        *(tempKey+3)  = *(key+23);
        *(tempKey+4)  = *(key+0);
        *(tempKey+5)  = *(key+4);
        *(tempKey+6)  = *(key+2);
        *(tempKey+7)  = *(key+27);
        *(tempKey+8)  = *(key+14);
        *(tempKey+9)  = *(key+5);
        *(tempKey+10) = *(key+20);
        *(tempKey+11) = *(key+9);
        *(tempKey+12) = *(key+22);
        *(tempKey+13) = *(key+18);
        *(tempKey+14) = *(key+11);
        *(tempKey+15) = *(key+3);
        *(tempKey+16) = *(key+25);
        *(tempKey+17) = *(key+7);
        *(tempKey+18) = *(key+15);
        *(tempKey+19) = *(key+6);
        *(tempKey+20) = *(key+26);
        *(tempKey+21) = *(key+19);
        *(tempKey+22) = *(key+12);
        *(tempKey+23) = *(key+1);
        *(tempKey+24) = *(key+40);
        *(tempKey+25) = *(key+51);
        *(tempKey+26) = *(key+30);
        *(tempKey+27) = *(key+36);
        *(tempKey+28) = *(key+46);
        *(tempKey+29) = *(key+54);
        *(tempKey+30) = *(key+29);
        *(tempKey+31) = *(key+39);
        *(tempKey+32) = *(key+50);
        *(tempKey+33) = *(key+44);
        *(tempKey+34) = *(key+32);
        *(tempKey+35) = *(key+47);
        *(tempKey+36) = *(key+43);
        *(tempKey+37) = *(key+48);
        *(tempKey+38) = *(key+38);
        *(tempKey+39) = *(key+55);
        *(tempKey+40) = *(key+33);
        *(tempKey+41) = *(key+52);
        *(tempKey+42) = *(key+45);
        *(tempKey+43) = *(key+41);
        *(tempKey+44) = *(key+49);
        *(tempKey+45) = *(key+35);
        *(tempKey+46) = *(key+28);
        *(tempKey+47) = *(key+31);
	//LOGD("Jas","generateKeys %d -->",i);
	//LOGD("Jas","generateKeys tempkey -->");
	//LOGBIT(tempKey, 48);
	//LOGD("Jas","generateKeys key -->");
	//LOGBIT(key, 56);
	//LOGD("Jas","generateKeys %d OVER",i);
        memcpy(keys+i*48,tempKey,48);
    }
    memcpy(Keys,keys,16*48);
    free(keys);
    free(key);
    free(tempKey);
}
void pPermute(char* sBoxByte,char* PBoxPermute){
    //char* sBoxByte = SBoxByte;
    char* pBoxPermute = malloc(32);
    memset(pBoxPermute,0,32);
    *(pBoxPermute+0)  = *(sBoxByte+15);
    *(pBoxPermute+1)  = *(sBoxByte+6);
    *(pBoxPermute+2)  = *(sBoxByte+19);
    *(pBoxPermute+3)  = *(sBoxByte+20);
    *(pBoxPermute+4)  = *(sBoxByte+28);
    *(pBoxPermute+5)  = *(sBoxByte+11);
    *(pBoxPermute+6)  = *(sBoxByte+27);
    *(pBoxPermute+7)  = *(sBoxByte+16);
    *(pBoxPermute+8)  = *(sBoxByte+0);
    *(pBoxPermute+9)  = *(sBoxByte+14);
    *(pBoxPermute+10) = *(sBoxByte+22);
    *(pBoxPermute+11) = *(sBoxByte+25);
    *(pBoxPermute+12) = *(sBoxByte+4);
    *(pBoxPermute+13) = *(sBoxByte+17);
    *(pBoxPermute+14) = *(sBoxByte+30);
    *(pBoxPermute+15) = *(sBoxByte+9);
    *(pBoxPermute+16) = *(sBoxByte+1);
    *(pBoxPermute+17) = *(sBoxByte+7);
    *(pBoxPermute+18) = *(sBoxByte+23);
    *(pBoxPermute+19) = *(sBoxByte+13);
    *(pBoxPermute+20) = *(sBoxByte+31);
    *(pBoxPermute+21) = *(sBoxByte+26);
    *(pBoxPermute+22) = *(sBoxByte+2);
    *(pBoxPermute+23) = *(sBoxByte+8);
    *(pBoxPermute+24) = *(sBoxByte+18);
    *(pBoxPermute+25) = *(sBoxByte+12);
    *(pBoxPermute+26) = *(sBoxByte+29);
    *(pBoxPermute+27) = *(sBoxByte+5);
    *(pBoxPermute+28) = *(sBoxByte+21);
    *(pBoxPermute+29) = *(sBoxByte+10);
    *(pBoxPermute+30) = *(sBoxByte+3);
    *(pBoxPermute+31) = *(sBoxByte+24);
    memcpy(PBoxPermute,pBoxPermute,32);
    free(pBoxPermute);
}
void finallyPermute(char* Permute){
     char* permute = malloc(64);
     memset(permute,0,64);
     *(permute+0)  = *(Permute+39);
     *(permute+1)  = *(Permute+7);
     *(permute+2)  = *(Permute+47);
     *(permute+3)  = *(Permute+15);
     *(permute+4)  = *(Permute+55);
     *(permute+5)  = *(Permute+23);
     *(permute+6)  = *(Permute+63);
     *(permute+7)  = *(Permute+31);
     *(permute+8)  = *(Permute+38);
     *(permute+9)  = *(Permute+6);
     *(permute+10) = *(Permute+46);
     *(permute+11) = *(Permute+14);
     *(permute+12) = *(Permute+54);
     *(permute+13) = *(Permute+22);
     *(permute+14) = *(Permute+62);
     *(permute+15) = *(Permute+30);
     *(permute+16) = *(Permute+37);
     *(permute+17) = *(Permute+5);
     *(permute+18) = *(Permute+45);
     *(permute+19) = *(Permute+13);
     *(permute+20) = *(Permute+53);
     *(permute+21) = *(Permute+21);
     *(permute+22) = *(Permute+61);
     *(permute+23) = *(Permute+29);
     *(permute+24) = *(Permute+36);
     *(permute+25) = *(Permute+4);
     *(permute+26) = *(Permute+44);
     *(permute+27) = *(Permute+12);
     *(permute+28) = *(Permute+52);
     *(permute+29) = *(Permute+20);
     *(permute+30) = *(Permute+60);
     *(permute+31) = *(Permute+28);
     *(permute+32) = *(Permute+35);
     *(permute+33) = *(Permute+3);
     *(permute+34) = *(Permute+43);
     *(permute+35) = *(Permute+11);
     *(permute+36) = *(Permute+51);
     *(permute+37) = *(Permute+19);
     *(permute+38) = *(Permute+59);
     *(permute+39) = *(Permute+27);
     *(permute+40) = *(Permute+34);
     *(permute+41) = *(Permute+2);
     *(permute+42) = *(Permute+42);
     *(permute+43) = *(Permute+10);
     *(permute+44) = *(Permute+50);
     *(permute+45) = *(Permute+18);
     *(permute+46) = *(Permute+58);
     *(permute+47) = *(Permute+26);
     *(permute+48) = *(Permute+33);
     *(permute+49) = *(Permute+1);
     *(permute+50) = *(Permute+41);
     *(permute+51) = *(Permute+9);
     *(permute+52) = *(Permute+49);
     *(permute+53) = *(Permute+17);
     *(permute+54) = *(Permute+57);
     *(permute+55) = *(Permute+25);
     *(permute+56) = *(Permute+32);
     *(permute+57) = *(Permute+0);
     *(permute+58) = *(Permute+40);
     *(permute+59) = *(Permute+8);
     *(permute+60) = *(Permute+48);
     *(permute+61) = *(Permute+16);
     *(permute+62) = *(Permute+56);
     *(permute+63) = *(Permute+24);
     memcpy(Permute,permute,64);
     free(permute);
}
void initPermute(char* decode,char* IpByte){
    char* ipByte = malloc(64);
    memset(ipByte,0,64);
    int i = 0, m = 1, n = 0, j, k;
    for (i = 0, m = 1, n = 0; i < 4; i++, m += 2, n += 2) {
        for (j = 7, k = 0; j >= 0; j--, k++) {
            *(ipByte+i*8+k)    = *(decode+j*8+m);
            *(ipByte+i*8+k+32) = *(decode+j*8+n);
        }
    }
    memcpy(IpByte,ipByte,64);
    free(ipByte);
}
void expandPermute(char* LeftDate,char* ExpandData){
    char* expandData = malloc(48);
    int i;
    for (i = 0; i < 8; i++) {
        if (i == 0) {
            *(expandData+i*6) = *(LeftDate+31);
        } else {
            *(expandData+i*6) = *(LeftDate+i*4-1);
        }
        *(expandData+i*6+1) = *(LeftDate+i*4+0);
        *(expandData+i*6+2) = *(LeftDate+i*4+1);
        *(expandData+i*6+3) = *(LeftDate+i*4+2);
        *(expandData+i*6+4) = *(LeftDate+i*4+3);
        if (i == 7) {
            *(expandData+i*6+5) = *LeftDate;
        } else {
            *(expandData+i*6+5) = *(LeftDate+i*4+4);
        }
    }
    memcpy(ExpandData,expandData,48);
    free(expandData);
}
void Xor(char* InA, char* InB ,int len)
{
    int i;
    for(i=0; i<len; i++)
        *(InA+i) ^= *(InB+i);
}
void dec(char* decode,char* decodeKey){
    char* dec_Keys  = malloc(16*48);
    memset(dec_Keys,0,16*48);
   
    char* IpByte    = malloc(64);
    memset(IpByte,0,64);
 
    char* ipLeft    = malloc(32);
    memset(ipLeft,0,32);
   
    char* ipRight   = malloc(32);
    memset(ipRight,0,32);

    char* tempLeft  = malloc(32);
    memset(tempLeft,0,32);

    char* tempRight = malloc(32);
    memset(tempRight,0,32);

    char* key       = malloc(48);
    memset(key,0,48);

    char* finalData = malloc(64);
    memset(finalData,0,64);
   

    int i = 0, j = 0, k = 0, m = 0, n = 0;
   
    generateKeys(decodeKey,dec_Keys);
 //   LOGD("Jas","KeysKeysKeysKeys======");
  //  for(i=0;i<16;i++)LOGBIT(dec_Keys+i*48,48);
 //  LOGD("Jas","\n\n\n");	
    initPermute(decode,IpByte);
 //   LOGD("Jas","ipByteipByteipByteipByte======");
//	LOGBIT(IpByte, 64);
    memcpy(ipLeft,IpByte,32);
    memcpy(ipRight,IpByte+32,32);
    /*temp data*/
    char* ExpandData = malloc(48);
    memset(ExpandData,0,48);
    char* SBoxByte   = malloc(32);
    memset(SBoxByte,0,32);

    for (i = 15; i >= 0; i--) {
        memcpy(tempLeft,ipLeft,32);
        memcpy(ipLeft,ipRight,32);
        memset(key,0,48);
        memcpy(key,dec_Keys+i*48,48);
        memset(ExpandData,0,48);
        memset(SBoxByte,0,32);
		//int[] tempRight = xor(pPermute(sBoxPermute(xor(
               //     expandPermute(ipRight), key))), tempLeft);
        expandPermute(ipRight,ExpandData);
	//LOGD("Jas","ExpandData1====\n");	
	//LOGBIT(ExpandData, 48);
        Xor(ExpandData,key,48);
	//LOGD("Jas","ExpandData2====\n");	
	//LOGBIT(ExpandData, 48);
        sBoxPermute(ExpandData,SBoxByte);
		//LOGD("Jas","SBoxByte1====\n");	
	//LOGBIT(SBoxByte, 32);
        pPermute(SBoxByte,SBoxByte);
		//LOGD("Jas","SBoxByte2====\n");	
	//LOGBIT(SBoxByte, 32);
        Xor(SBoxByte,tempLeft,32);
		//LOGD("Jas","SBoxByte3====\n");	
	//LOGBIT(SBoxByte, 32);
        memcpy(tempRight,SBoxByte,32);
        memcpy(ipRight,tempRight,32);
    }
    memset(finalData,0,64);
    memcpy(finalData,ipRight,32);
    memcpy(finalData+32,ipLeft,32);
  // LOGD("Jas","finalDatafinalDatafinalDatafinalData======");
   // LOGBIT(finalData, 64);
    finallyPermute(finalData);
   //LOGD("Jas","finallyPermutefinallyPermutefinallyPermute======");
 // LOGBIT(finalData, 64);
    memcpy(decode,finalData,64);
    free(finalData);
    free(SBoxByte);
    free(ExpandData);
    free(key);
    free(tempRight);
    free(tempLeft);
    free(ipRight);
    free(ipLeft);
    free(IpByte);
    free(dec_Keys);
}
unsigned char StrToInt(char* str){
    unsigned char value = *str;
    if(value<=57 && value>=48){
        *str = value-48;
        return true;
    }else if(value<=70 && value>=65){
        *str = value-65+10;
        return true;
    }else if(value<=102 && value>=97){
        *str = value-97+10;
        return true;
    }
    return false;
}
unsigned char IntToStr(char* value){
    unsigned char Value = *value;
    if(Value>=0 && Value<=9){
        *value = 48+Value;
        return true;
    }else if(Value>=10 && Value<=15){
        *value = 65+Value-10;
        return true;
    }else
        return false;
}
void strToBit(char* Str,char*Bit){
    char* str = malloc(KEYCODE_DECODE);
    char* bit = malloc(KEYCODE_LENG);
    memset(bit,0,KEYCODE_LENG);
    memset(str,0,KEYCODE_DECODE);
    memcpy(str,Str,KEYCODE_DECODE);
    int i =0,j=0;
    char temp = 0;
    for(i=0;i<KEYCODE_DECODE;i++){
        temp = *(str+i);
        if(StrToInt(&temp)){
            for(j=0;j<4;j++){
                if(temp&0x0008)
                    strcat(bit,"1");
                else
                    strcat(bit,"0");
                temp=temp<<1;
            }
        }
    }
    for(i=0;i<KEYCODE_LENG;i++)
        (*(bit+i))=(*(bit+i))-48;
    memcpy(Bit,bit,KEYCODE_LENG);	
    //LOGD("Jas","strToBit----\n");
   // LOGSTR(Str, KEYCODE_DECODE);
   // LOGD("Jas","\n");
   // LOGSTR(str, KEYCODE_DECODE);
//	 LOGD("Jas","\n");
    //LOGBIT(bit, KEYCODE_LENG);
	// LOGD("Jas","\n");
	 free(bit);
	 free(str);
}

void strToBt(char* str,char* Bt){
    int i = 0, j = 0, p = 0, q = 0, m = 0;
    int leng = strlen(str);
    char bt[KEYCODE_LENG];
    memset(bt,0,sizeof(bt));
    if(leng<4){
         for (i = 0; i < leng; i++) {
            int k = *(str+i);
            for (j = 0; j < 16; j++) {
                int pow = 1, m = 0;
                for (m = 15; m > j; m--) {
                    pow *= 2;
                }
                bt[16 * i + j] = (k / pow) % 2;
            }
        }
        for (p = leng; p < 4; p++) {
            int k = 0;
            for (q = 0; q < 16; q++) {
                int pow = 1, m = 0;
                for (m = 15; m > q; m--) {
                    pow *= 2;
                }
                bt[16 * p + q] = (k / pow) % 2;
            }
        }
    }else{
        for (i = 0; i < 4; i++) {
            int k = *(str+i);
            for ( j = 0; j < 16; j++) {
                int pow = 1;
                for ( m = 15; m > j; m--) {
                    pow *= 2;
                }
                bt[16 * i + j] = (k / pow) % 2;
                p = 16*i+j;
            }

        }
    }
    memcpy(Bt,bt,sizeof(bt));
}
int getKeyBytes(char* key,char* keylist,int keylistleng){
     int leng      = strlen(key);
     int index     = (leng / KEYCODE);
     int remainder = leng % KEYCODE;
     int i = 0;
     char* ye      = malloc(keylistleng);
     if(!ye)return false;
     char keystr[KEYCODE+1];
     memset(ye,0,sizeof(ye));
     for(i=0;i<index;i++){
        memset(keystr,0,KEYCODE+1);
        memcpy(keystr,key+KEYCODE*i,KEYCODE);
        strToBt(keystr,ye+i*KEYCODE_LENG);
     }
     if(remainder>0){
        memset(keystr,0,KEYCODE+1);
        memcpy(keystr,key+KEYCODE*index,remainder);
        strToBt(keystr,ye+index*KEYCODE_LENG);
     }
     memcpy(keylist,ye,keylistleng);
     free(ye);
     return true;
}
/*void StrToHex(char* str){
    unsigned char value[KEYCODE_DECODE+1];
    int   leng = strlen(str);
    char* p = malloc(leng);
    memset(value,0,sizeof(value));
    memset(p,0,leng);
    memcpy(value,str,((sizeof(str)>KEYCODE_DECODE)?KEYCODE_DECODE:sizeof(str)));
    sscanf(value,"%02X",p);
    memset(str,0,leng);
    memcpy(str,p,leng);
    free(p);
}*/
void byteToString(char* BitData,char* BitString){
     char* bitString = malloc(65);
     memset(bitString,0,65);
     char* tempchar  = malloc(2);
     memset(tempchar,0,2);
     int i,j,m,k,pow;
    // printf("byteToString=%s\n",BitData);
     for ( i = 0; i < 4; i++) {
       // printf("byteToString1=%d\n",i);
        k = 0;
        for ( j = 0; j < 16; j++) {
            pow = 1;
            for ( m = 15; m > j; m--) {
                pow *= 2;
            }
            k += (*(BitData+16*i+j))*pow;
        }
        //printf("byteToString2=%d\n",k);
        //k=k&0x00FF;
        //printf("byteToString2=%d\n",k);
        if (k != 0) {
            memset(tempchar,0,2);
            *tempchar = (char)k;
            strcat(bitString,tempchar);
        }
        //printf("byteToString3=%s\n",bitString);
    }
    //strcat(BitString,bitString);
    memcpy(BitString,bitString,64);
    *(BitString+65)=0;
   // printf("BitString=%s",BitString);
    free(bitString);
}

void debug(char* str,char* Key,char* Result){
   char* NeedDecodeStr    = str;
   int   leng    = strlen(str);
   int   KeyLeng = strlen(Key);
   //use to save decode
   int   index     = KeyLeng/KEYCODE;
   char* decode    = malloc(KEYCODE_LENG);
   char* decodeKey = malloc(KEYCODE_LENG);
   char* decodeStr = malloc(KEYCODE_DECODE);
   memset(decode,0,KEYCODE_LENG);

   int   keylistleng = sizeof(char)*KEYCODE_LENG*(KeyLeng/KEYCODE+(KeyLeng%KEYCODE>0));
   char* keylist     = malloc(keylistleng);
   memset(keylist,0,keylistleng);

   char* ResultData = malloc(leng/KEYCODE_DECODE*KEYCODE_LENG+1);
   memset(ResultData,0,leng/KEYCODE_DECODE*KEYCODE_LENG+1);
   char* ResultDataString = malloc(KEYCODE_LENG+1);
   memset(ResultDataString,0,KEYCODE_LENG+1);

   int    i,j,k;

   getKeyBytes(Key,keylist,keylistleng);
   index = leng/KEYCODE_DECODE;
   //LOGD("Jas","Start dec %d=====%d=================",index,(KeyLeng/KEYCODE+(KeyLeng%KEYCODE>0)-1));
   for(i=0;i<index;i++){
        memset(decodeStr,0,KEYCODE_DECODE);
        memcpy(decodeStr,NeedDecodeStr+i*KEYCODE_DECODE,KEYCODE_DECODE);
        memset(decode,0,KEYCODE_LENG);
       
        strToBit(decodeStr,decode);
        //LOGD("Jas","Start dec %d",i);
	 //LOGSTR(decodeStr, KEYCODE_DECODE);
	 //LOGD("Jas","\n");
        for (j=(KeyLeng/KEYCODE+(KeyLeng%KEYCODE>0)-1);j>= 0;j--){
            memset(decodeKey,0,KEYCODE_LENG);
            memcpy(decodeKey,keylist+j*KEYCODE_LENG,KEYCODE_LENG);
	     //LOGD("Jas","===decode=%d ===",j);
            //LOGBIT(decode,64);
	     //LOGD("Jas","+++decode+%d +++",j);
	     //LOGD("Jas","===decodeKey=%d ===",j);
            //LOGBIT(decodeKey,64);
	     //LOGD("Jas","+++decodeKey+%d +++",j);
            dec(decode,decodeKey);
        }
        //LOGD("Jas","&&&&&&&&decode =============");
        //LOGBIT(decode,64);
	 //LOGD("Jas","&&&&&&&&decode +++++++++++++");
        memset(ResultDataString,0,65);
        byteToString(decode,ResultDataString);
	//LOGD("Jas","&&&&&&&&ResultDataString=%s",ResultDataString);
        strcat(ResultData,ResultDataString);
		//LOGD("Jas","ResultData=%s",ResultData);
   }

   memcpy(Result,ResultData,strlen(ResultData));
   free(decode);
   free(decodeKey);
   free(decodeStr);
   free(keylist);
   free(ResultData);
   free(ResultDataString);
}

