//
// Created by Oliver Mulherin on 29/9/17.
//

#include <jni.h>
#include <stdlib.h>



#include "CCurl.h"
extern "C" {
    #include "pearl_diver.h"
    #include "converter.h"
    #include "curl.h"
}

extern "C" {
JNIEXPORT void JNICALL Java_ccurl_CCURLLib_init(JNIEnv *env, jobject obj);
JNIEXPORT jstring JNICALL
Java_ccurl_CCURLLib_pow(JNIEnv *env, jobject obj, jstring trytes,
                                    jint minWeight, jint offset);
};


JNIEXPORT void JNICALL
Java_ccurl_CCURLLib_init(JNIEnv *env, jobject obj) {


//    init_pearldiver(&pd);


}

JNIEXPORT jstring JNICALL
Java_ccurl_CCURLLib_pow(JNIEnv *env, jobject obj, jstring trytes,
                                    jint minWeight, jint offset) {
    jstring resret;

    const char *trytesc = env->GetStringUTFChars(trytes, 0);
    int len =  strlen(trytesc);


    ALOGV("input len %d str %s", len, trytesc);

    if(len != TRYTE_LENGTH)
        return NULL;

    char* trits = trits_from_trytes(trytesc, len);
    char* buf = NULL;


    PearlDiver pd;

    curl_t curl;
    init_curl(&curl);
    ALOGV("Curl init'ed");
    absorb(&curl, trits, TRANSACTION_LENGTH - HASH_LENGTH);
    ALOGV("Curl absorbed");

    memcpy(&curl.state, &trits[TRANSACTION_LENGTH - HASH_LENGTH], HASH_LENGTH * sizeof(char));

    ALOGV("Starting Search");

    pd_search(&pd, &curl, minWeight, -1);


    env->ReleaseStringUTFChars(trytes, trytesc);

    if (pd.status == PD_FOUND) {
        memcpy(&trits[TRANSACTION_LENGTH - HASH_LENGTH], &curl.state, HASH_LENGTH * sizeof(char));
        buf = trytes_from_trits(trits, 0, TRANSACTION_LENGTH);

        env->ReleaseStringUTFChars(trytes, trytesc);
        resret = env->NewStringUTF((const char*)buf);
//        ALOGV("done len %d str %s", len, &buf[TRANSACTION_LENGTH - HASH_LENGTH]);
        return resret;
    }


    ALOGV("ERROR");

    return NULL;



}
