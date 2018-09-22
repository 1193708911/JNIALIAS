#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jboolean

JNICALL
Java_com_example_administrator_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject context/* this */) {
    //获取当前的签名hash值进行对比
    jclass jclassContext = env->GetObjectClass(context);
    //获取packgemanager
    jmethodID jPackagerManagerMethodId = env->GetMethodID(jclassContext, "getPackageManager",
                                                          "()Landroid/content/pm/PackageManager;");
    //拿到packagerManger
    jobject jPackageMangerObject = env->CallObjectMethod(context, jPackagerManagerMethodId);

    jclass jPackageClass = env->GetObjectClass(jPackageMangerObject);
//获取就packagerInfo
    jmethodID jPackagerInfoMehtodId = env->GetMethodID(jPackageClass, "getPackageInfo",
                                                       "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");

    jmethodID jGetPackNameMethodId = env->GetMethodID(jclassContext, "getPackageName",
                                                      "()Ljava/lang/String;");
    jstring pkg_name = (jstring) env->CallObjectMethod(context, jGetPackNameMethodId);
    //拿到packagerinfo对象
    jobject jPackagerInfoObject = env->CallObjectMethod(jPackageMangerObject,
                                                        jPackagerInfoMehtodId, pkg_name, 64);

    jclass jPackagerInfoClass = env->GetObjectClass(jPackagerInfoObject);
    jfieldID jfieldID1 = env->GetFieldID(jPackagerInfoClass, "signatures",
                                         "[Landroid/content/pm/Signature;");

    jobject jSigingNarueObject = env->GetObjectField(jPackagerInfoObject, jfieldID1);

    jobjectArray jSignatureArray = (jobjectArray) jSigingNarueObject;

    jobject jSignature = env->GetObjectArrayElement(jSignatureArray, 0);
    jclass jSignatureClass = env->GetObjectClass(jSignature);
    jmethodID jSignatureToCharsMethodId = env->GetMethodID(jSignatureClass, "hashCode", "()I");

    jint hashCode = (jint) env->CallIntMethod(jSignature, jSignatureToCharsMethodId);

    if (hashCode == NULL || hashCode != (-1858809270)) {
        return false;
    }
    return true;
}
