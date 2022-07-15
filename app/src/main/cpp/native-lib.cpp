#include <jni.h>
#include <string>

#include "mbedtls/build_info.h"

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdlib.h>
#include <stdio.h>
#define mbedtls_printf       printf
#define mbedtls_exit         exit
#define MBEDTLS_EXIT_SUCCESS EXIT_SUCCESS
#define MBEDTLS_EXIT_FAILURE EXIT_FAILURE
#endif

#if defined(MBEDTLS_MD5_C)
#include "mbedtls/md5.h"
#endif

#if !defined(MBEDTLS_MD5_C)
extern "C" JNIEXPORT jstring JNICALL
Java_com_gebulot_tls_1bridge_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    mbedtls_printf("MBEDTLS_MD5_C not defined.\n");
    mbedtls_exit( 0 );
}
#else


extern "C" JNIEXPORT jstring JNICALL
Java_com_gebulot_tls_1bridge_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    int i, ret;
    unsigned char digest[16];
    char str[] = "Hello, world!";

    mbedtls_printf( "\n  MD5('%s') = ", str );

    if( ( ret = mbedtls_md5( (unsigned char *) str, 13, digest ) ) != 0 )
        //mbedtls_exit( MBEDTLS_EXIT_FAILURE );
        return env->NewStringUTF("MBEDTLS_EXIT_FAILURE");

    for( i = 0; i < 16; i++ )
        mbedtls_printf( "%02x", digest[i] );

    mbedtls_printf( "\n\n" );

    //mbedtls_exit( MBEDTLS_EXIT_SUCCESS );
    return env->NewStringUTF("MBEDTLS_EXIT_SUCCESS");


}
#endif /* MBEDTLS_MD5_C */