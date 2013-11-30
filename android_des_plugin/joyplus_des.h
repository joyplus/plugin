#ifndef _JOYPLUS_DES_H
#define _JOYPLUS_DES_H
#include <android/log.h>

//void Log(char* log);
//void LogNumber(char* log,int len);
#define  LOGD(LOG_TAG ,...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)


/*for encode or decode need size is 4*/
#define KEYCODE       4
/*for 64 + '\0'*/
#define KEYCODE_LENG  64
/*for decode need 16*/
#define KEYCODE_DECODE 16


#ifndef true
 #define true 1
#endif

#ifndef false
 #define false 0
#endif

void debug(char* str,char* Key,char* Result);
#endif // _JOYPLUS_DES_H
