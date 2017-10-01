//
// Created by Oliver Mulherin on 29/9/17.
//

#include <jni.h>
#include <stdlib.h>



#include "CCurl.h"
extern "C" {
    #include "pearl_diver.h"
    #include "converter.h"
}

extern "C" {
JNIEXPORT void JNICALL Java_ccurl_CCURLLib_init(JNIEnv *env, jobject obj);
JNIEXPORT jstring JNICALL
Java_ccurl_CCURLLib_pow(JNIEnv *env, jobject obj, jstring trytes,
                                    jint minWeight, jint offset);
};

PearlDiver pd;

JNIEXPORT void JNICALL
Java_ccurl_CCURLLib_init(JNIEnv *env, jobject obj) {


//    init_pearldiver(&pd);


}

JNIEXPORT jstring JNICALL
Java_ccurl_CCURLLib_pow(JNIEnv *env, jobject obj, jstring trytes,
                                    jint minWeight, jint offset) {
    jstring resret;

    init_converter();

    const char *trytesc = env->GetStringUTFChars(trytes, 0);
    int len =  strlen(trytesc);
    ALOGV("input len %d str %s", len, trytesc);
    char* trits = trits_from_trytes(trytesc, len);

    pd_search(&pd, trits, len * 3, minWeight, 0);

    char * trytesDone = trytes_from_trits(trits, offset, len * 3);
    ALOGV("done len %d str %s", len, trytesDone);

    env->ReleaseStringUTFChars(trytes, trytesc);
    resret = env->NewStringUTF((const char*)trytesDone);
    return resret;


}
