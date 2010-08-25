/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class net_fhtagn_zoob_zoobRenderer */

#ifndef _Included_net_fhtagn_zoob_zoobRenderer
#define _Included_net_fhtagn_zoob_zoobRenderer
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     net_fhtagn_zoob_zoobRenderer
 * Method:    nativeInit
 * Signature: (S, L/net.fhtagn.zoob/ZoobApplication, S)V
 */
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_nativeInit
  (JNIEnv *, jclass, jstring, jobject, jstring);

/*
 * Class:     net_fhtagn_zoob_zoobRenderer
 * Method:    nativeStartGame
 * Signature: (S)V
 */
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_nativeStartGame
  (JNIEnv *, jclass, int);


/*
 * Class:     net_fhtagn_zoob_zoobRenderer
 * Method:    nativeInitGL
 * Signature: (I,I,I)V
 */
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_nativeInitGL
  (JNIEnv *, jclass, int, int, int, int);

/*
 * Class:     net_fhtagn_zoob_zoobRenderer
 * Method:    nativeResize
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_nativeResize
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     net_fhtagn_zoob_zoobRenderer
 * Method:    nativeRender
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_nativeRender
  (JNIEnv *, jclass);

/*
 * Class:     net_fhtagn_zoob_zoobGLSurface
 * Method:    nativePause
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_nativePause
  (JNIEnv *, jclass);

/*
 * Class:     net_fhtagn_zoob_zoobGLSurface
 * Method:    event callbacks
 * Signature: (FF)V
 */
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_touchEventDown
  (JNIEnv *, jclass, jfloat, jfloat);
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_touchEventMove
  (JNIEnv *, jclass, jfloat, jfloat);
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_touchEventDown
  (JNIEnv *, jclass, jfloat, jfloat);
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_touchEventUp
  (JNIEnv *, jclass, jfloat, jfloat);
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_touchEventOther
  (JNIEnv *, jclass, jfloat, jfloat);
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_trackballMove
  (JNIEnv *, jclass, jfloat, jfloat);
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_trackballClick
  (JNIEnv *, jclass, jfloat, jfloat);

//Multitouch
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_touchEventSecondaryDown
  (JNIEnv *, jclass, jfloat, jfloat);
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_touchEventSecondaryUp
  (JNIEnv *, jclass, jfloat, jfloat);
JNIEXPORT void JNICALL Java_net_fhtagn_zoobgame_ZoobRenderer_touchEventSecondaryMove
  (JNIEnv *, jclass, jfloat, jfloat);

#ifdef __cplusplus
}
#endif
#endif
