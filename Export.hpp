#ifndef Export_H
#define Export_H

/*#define JNIClassPath(X)  Java_InterfaceManager_Main_ ## X
#include <jni.h>

#ifdef __cplusplus
extern "C"
{
#endif

	JNIEXPORT jboolean JNICALL JNIClassPath(addPrinter)(JNIEnv*, jobject);
	JNIEXPORT jboolean JNICALL JNIClassPath(addPrinters)(JNIEnv*, jobject, jlong);
	JNIEXPORT jboolean JNICALL JNIClassPath(clearPrinters)(JNIEnv*, jobject);
	JNIEXPORT jlong JNICALL JNIClassPath(getPrinterCount)(JNIEnv*, jobject);
	JNIEXPORT jlong JNICALL JNIClassPath(getSelectionIndex)(JNIEnv*, jobject);
	JNIEXPORT jboolean JNICALL JNIClassPath(selectPrinterIndex)(JNIEnv*, jobject, jlong);

	JNIEXPORT jboolean JNICALL JNIClassPath(setCOMBaudRate)(JNIEnv*, jobject, jint);
	JNIEXPORT jboolean JNICALL JNIClassPath(setCOMByteSize)(JNIEnv*, jobject, jbyte);
	JNIEXPORT jboolean JNICALL JNIClassPath(setCOMParity)(JNIEnv*, jobject, jbyte);
	JNIEXPORT jboolean JNICALL JNIClassPath(setCOMPort)(JNIEnv*, jobject, jstring);
	JNIEXPORT jboolean JNICALL JNIClassPath(setCOMStopBits)(JNIEnv*, jobject, jbyte);
	JNIEXPORT jboolean JNICALL JNIClassPath(setCOMTimeout)(JNIEnv*, jobject, jlong);
	JNIEXPORT jint JNICALL JNIClassPath(getCOMBaudRate)(JNIEnv*, jobject);
	JNIEXPORT jboolean JNICALL JNIClassPath(getCOMIsBluetooth)(JNIEnv*, jobject);
	JNIEXPORT jbyte JNICALL JNIClassPath(getCOMByteSize)(JNIEnv*, jobject);
	JNIEXPORT jbyte JNICALL JNIClassPath(getCOMParity)(JNIEnv*, jobject);
	JNIEXPORT jstring JNICALL JNIClassPath(getCOMPort)(JNIEnv*, jobject);
	JNIEXPORT jbyte JNICALL JNIClassPath(getCOMStopBits)(JNIEnv*, jobject);
	JNIEXPORT jlong JNICALL JNIClassPath(getCOMTimeout)(JNIEnv*, jobject);

	JNIEXPORT jboolean JNICALL JNIClassPath(setLANAddress)(JNIEnv*, jobject, jstring);
	JNIEXPORT jboolean JNICALL JNIClassPath(setLANPort)(JNIEnv*, jobject, jshort);
	JNIEXPORT jboolean JNICALL JNIClassPath(setLANTimeout)(JNIEnv*, jobject, jlong);
	JNIEXPORT jstring JNICALL JNIClassPath(getLANAddress)(JNIEnv*, jobject);
	JNIEXPORT jshort JNICALL JNIClassPath(getLANPort)(JNIEnv*, jobject);
	JNIEXPORT jlong JNICALL JNIClassPath(getLANTimeout)(JNIEnv*, jobject);

	JNIEXPORT jboolean JNICALL JNIClassPath(setLPTPort)(JNIEnv*, jobject, jstring);
	JNIEXPORT jboolean JNICALL JNIClassPath(setLPTTimeout)(JNIEnv*, jobject, jlong);
	JNIEXPORT jstring JNICALL JNIClassPath(getLPTPort)(JNIEnv*, jobject);
	JNIEXPORT jlong JNICALL JNIClassPath(getLPTTimeout)(JNIEnv*, jobject);

	JNIEXPORT jboolean JNICALL JNIClassPath(setUSBDevicePath)(JNIEnv*, jobject, jstring);
	JNIEXPORT jboolean JNICALL JNIClassPath(setUSBTimeout)(JNIEnv*, jobject, jlong);
	JNIEXPORT jstring JNICALL JNIClassPath(getUSBDevicePath)(JNIEnv*, jobject);
	JNIEXPORT jlong JNICALL JNIClassPath(getUSBTimeout)(JNIEnv*, jobject);

	JNIEXPORT jstring JNICALL JNIClassPath(getPrinterType)(JNIEnv*, jobject);
	JNIEXPORT jboolean JNICALL JNIClassPath(setPrinterType)(JNIEnv*, jobject, jstring);

	JNIEXPORT jboolean JNICALL JNIClassPath(openCOMPort)(JNIEnv*, jobject);
	JNIEXPORT jstring JNICALL JNIClassPath(readCOMString)(JNIEnv*, jobject, jlong);
	JNIEXPORT jbyteArray JNICALL JNIClassPath(readCOMData)(JNIEnv*, jobject, jlong);
	JNIEXPORT jboolean JNICALL JNIClassPath(writeCOMString)(JNIEnv*, jobject, jstring);
	JNIEXPORT jboolean JNICALL JNIClassPath(writeCOMData)(JNIEnv*, jobject, jbyteArray);
	JNIEXPORT jboolean JNICALL JNIClassPath(closeCOMPort)(JNIEnv*, jobject);

	JNIEXPORT jboolean JNICALL JNIClassPath(openLANPort)(JNIEnv*, jobject);
	JNIEXPORT jstring JNICALL JNIClassPath(readLANString)(JNIEnv*, jobject, jlong);
	JNIEXPORT jbyteArray JNICALL JNIClassPath(readLANData)(JNIEnv*, jobject, jlong);
	JNIEXPORT jboolean JNICALL JNIClassPath(writeLANString)(JNIEnv*, jobject, jstring);
	JNIEXPORT jboolean JNICALL JNIClassPath(writeLANData)(JNIEnv*, jobject, jbyteArray);
	JNIEXPORT jboolean JNICALL JNIClassPath(closeLANPort)(JNIEnv*, jobject);

	JNIEXPORT jboolean JNICALL JNIClassPath(openLPTPort)(JNIEnv*, jobject);
	JNIEXPORT jstring JNICALL JNIClassPath(readLPTString)(JNIEnv*, jobject, jlong);
	JNIEXPORT jbyteArray JNICALL JNIClassPath(readLPTData)(JNIEnv*, jobject, jlong);
	JNIEXPORT jboolean JNICALL JNIClassPath(writeLPTString)(JNIEnv*, jobject, jstring);
	JNIEXPORT jboolean JNICALL JNIClassPath(writeLPTData)(JNIEnv*, jobject, jbyteArray);
	JNIEXPORT jboolean JNICALL JNIClassPath(closeLPTPort)(JNIEnv*, jobject);

	JNIEXPORT jboolean JNICALL JNIClassPath(openUSBPort)(JNIEnv*, jobject);
	JNIEXPORT jstring JNICALL JNIClassPath(readUSBString)(JNIEnv*, jobject, jlong);
	JNIEXPORT jbyteArray JNICALL JNIClassPath(readUSBData)(JNIEnv*, jobject, jlong);
	JNIEXPORT jboolean JNICALL JNIClassPath(writeUSBString)(JNIEnv*, jobject, jstring);
	JNIEXPORT jboolean JNICALL JNIClassPath(writeUSBData)(JNIEnv*, jobject, jbyteArray);
	JNIEXPORT jboolean JNICALL JNIClassPath(closeUSBPort)(JNIEnv*, jobject);

	JNIEXPORT void JNICALL JNIClassPath(enableErrorLog)(JNIEnv*, jobject);
	JNIEXPORT void JNICALL JNIClassPath(disableErrorLog)(JNIEnv*, jobject);
	JNIEXPORT jstring JNICALL JNIClassPath(dumpErrorLog)(JNIEnv*, jobject);

	JNIEXPORT jobject JNICALL JNIClassPath(getCOMPorts)(JNIEnv*, jobject);
	JNIEXPORT jobject JNICALL JNIClassPath(getLPTPorts)(JNIEnv*, jobject);
	JNIEXPORT jobject JNICALL JNIClassPath(getUSBDevicePaths)(JNIEnv*, jobject);

#ifdef __cplusplus
}
#endif*/
#endif