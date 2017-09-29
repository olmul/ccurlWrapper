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
JNIEXPORT void JNICALL Java_com_rnccurl_CCURLLib_init(JNIEnv *env, jobject obj);
JNIEXPORT jstring JNICALL
Java_com_rnccurl_CCURLLib_pow(JNIEnv *env, jobject obj, jstring trytes,
                                    jint minWeight, jint offset);
};

PearlDiver pd;

JNIEXPORT void JNICALL
Java_com_rnccurl_CCURLLib_init(JNIEnv *env, jobject obj) {

    init_converter();
//    init_pearldiver(&pd);

    ALOGV("CREATED PEARLDRIVER");
}

JNIEXPORT jstring JNICALL
Java_com_rnccurl_CCURLLib_pow(JNIEnv *env, jobject obj, jstring trytes,
                                    jint minWeight, jint offset) {
    jstring resret;

    const char *trytesc = env->GetStringUTFChars(trytes, 0);
    int len =  strlen(trytesc);

    char* trits = trits_from_trytes(trytesc, len);

    pd_search(&pd, trits, len * 3, minWeight, 0);

    char * trytesDone = trytes_from_trits(trits, offset, len * 3);


    env->ReleaseStringUTFChars(trytes, trytesc);
    resret = env->NewStringUTF((const char*)trytesDone);
    return resret;


}
