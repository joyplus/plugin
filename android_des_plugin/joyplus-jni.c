/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include <stdio.h>
#include "joyplus_des.h"

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/hellojni/HelloJni.java
 */
jstring
Java_com_joyplus_des_JoyplusDes_stringFromJNI( JNIEnv* env,
                                                  jobject thiz )
{
    char* str = "A9346827618761F6A9346827618761F6";
    char* Key = "ilovejoy";
    int  ResultLeng = strlen(str)/KEYCODE_DECODE*KEYCODE_LENG+1;
    char* Result = malloc(ResultLeng);
    memset(Result,0,ResultLeng);
    debug(str,Key,Result);
	//LOGD("Jas","%s",Result);
    return (*env)->NewStringUTF(env, Result);
}

jstring
Java_com_joyplus_des_JoyplusDes_DesstringFromJNI( JNIEnv* env,
                                                  jobject thiz ,jstring data)
{
   
    char * str = (char *) (*env)->GetStringUTFChars(env, data, 0);
    char* Key = "ilovejoy";
    int  ResultLeng = strlen(str)/KEYCODE_DECODE*KEYCODE_LENG+1;
    char* Result = malloc(ResultLeng);
    memset(Result,0,ResultLeng);
    debug(str,Key,Result);
	//LOGD("Jas","%s",Result);
    return (*env)->NewStringUTF(env, Result);
}


