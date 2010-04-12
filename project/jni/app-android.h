/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class net_fhtagn_moob_MoobRenderer */

#ifndef _Included_net_fhtagn_moob_MoobRenderer
#define _Included_net_fhtagn_moob_MoobRenderer
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     net_fhtagn_moob_MoobRenderer
 * Method:    nativeInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_net_fhtagn_moob_MoobRenderer_nativeInit
  (JNIEnv *, jclass, jstring);

/*
 * Class:     net_fhtagn_moob_MoobRenderer
 * Method:    nativeResize
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_net_fhtagn_moob_MoobRenderer_nativeResize
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     net_fhtagn_moob_MoobRenderer
 * Method:    nativeRender
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_net_fhtagn_moob_MoobRenderer_nativeRender
  (JNIEnv *, jclass);

/*
 * Class:     net_fhtagn_moob_MoobGLSurface
 * Method:    nativeMenu
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_net_fhtagn_moob_MoobGLSurface_nativeMenu
  (JNIEnv *, jclass);

/*
 * Class:     net_fhtagn_moob_MoobGLSurface
 * Method:    event callbacks
 * Signature: (FF)V
 */
JNIEXPORT void JNICALL Java_net_fhtagn_moob_MoobGLSurface_touchEventDown
  (JNIEnv *, jclass, jfloat, jfloat);
JNIEXPORT void JNICALL Java_net_fhtagn_moob_MoobGLSurface_touchEventMove
  (JNIEnv *, jclass, jfloat, jfloat);
JNIEXPORT void JNICALL Java_net_fhtagn_moob_MoobGLSurface_touchEventUp
  (JNIEnv *, jclass, jfloat, jfloat);
JNIEXPORT void JNICALL Java_net_fhtagn_moob_MoobGLSurface_touchEventOther
  (JNIEnv *, jclass, jfloat, jfloat);

#ifdef __cplusplus
}
#endif
#endif
