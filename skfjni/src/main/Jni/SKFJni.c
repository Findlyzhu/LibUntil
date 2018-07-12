#include <stdlib.h>
#include <malloc.h>
#include "com_ccore_jni_SKFJni.h"
#include "prebuilt/include/SKF.h"
#include <android/log.h>
#include <string.h>

#define TAG "SKF_CC"
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#define IF_ERROR_GOTO_END(x) if(x!=0) goto END;

#ifndef ANDROID
#define ANDROID
#endif

DEVHANDLE hDev = NULL_PTR;
HANDLE * hKey = NULL_PTR;
HAPPLICATION * hAppHandle = NULL_PTR;
HCONTAINER * hContainerHandle = NULL_PTR;
/*
 * 枚举并连接设备
 */
JNIEXPORT jlong JNICALL Java_com_ccore_jni_SKFJni_SKF_1ConnectDev(
		JNIEnv *env, jobject obj) {
	ULONG uiRet = 0;
	LPSTR szNameList = (LPSTR)malloc(1024);
	ULONG pulSize = 1024;

    LOGE("SKF_SO CALL:SKF_EnumDev");

	uiRet = SKF_EnumDev(1, szNameList, &pulSize);
	LOGE("SKF_EnumDev----return:%ld,szNameList = %s,pulSize = %ld", uiRet,uiRet,szNameList, pulSize);
	if(uiRet){
		free(szNameList);
		return uiRet;
	}
    LOGE("SKF_SO CALL:SKF_ConnectDev");
	uiRet = SKF_ConnectDev((LPSTR)szNameList, &hDev);
	LOGE("SKF_ConnectDev----return:%d , szNameList:=%s", uiRet,szNameList);
	free(szNameList);
	return uiRet;
}

/*
 * 断开设备连接
 */

JNIEXPORT jlong JNICALL Java_com_ccore_jni_SKFJni_SKF_1DisconnectDev(
		JNIEnv *env, jobject obj) {

	ULONG uiRet = 0;
	uiRet = SKF_DisconnectDev(hDev);
    hDev = NULL_PTR;
	return uiRet;
}

JNIEXPORT jlong JNICALL Java_com_ccore_jni_SKFJni_SKF_1SetAppPath(
		JNIEnv *env, jobject obj, jbyteArray szAppPath) {
	unsigned long uiRet = 0;
    LOGE("SKF_SetAppPath_JNI----Enter");
    jsize len = (*env)->GetArrayLength(env,szAppPath);
    char* appPath = (char*)malloc(len+1);
    if(NULL == appPath){
        uiRet = SAR_MEMORYERR;
        return uiRet;
    }
    memset(appPath,0,len+1);
    memcpy(appPath,(char*)(*env)->GetByteArrayElements(env,szAppPath,0),len);
    LOGE("V_SetAppPath:%s",appPath);
	uiRet = V_SetAppPath(appPath);
    if(appPath != NULL) free(appPath);
    LOGE("SKF_SetAppPath_JNI----return = %d",uiRet);
	return uiRet;
}