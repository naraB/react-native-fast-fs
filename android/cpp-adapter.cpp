#include <jni.h>
#include <jsi/jsi.h>
#include "FastFilesystemModule.h"

using namespace facebook;

extern "C" JNIEXPORT void JNICALL
Java_com_reactnativefastfs_FastFsModule_nativeInstall(JNIEnv *env, jobject clazz, jlong jsiPtr, jstring path)
{
    auto runtime = reinterpret_cast<jsi::Runtime *>(jsiPtr);
    if (runtime)
    {
        install(*runtime);
    }
}
