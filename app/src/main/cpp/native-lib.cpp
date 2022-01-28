#include <jni.h>
#include <string>
#include <AudioSaveEngine.h>
#include <logging_macros.h>

static AudioSaveEngine *engine = nullptr;

extern "C" {

JNIEXPORT void JNICALL
Java_com_example_audiosave_AudioEngine_create(JNIEnv *env, jclass clazz,
        jint input_device_id, jint input_channel_count) {

    if (engine != nullptr) {
        LOGE("Error creating audio engine, engine already created");
    } else {
        engine = new AudioSaveEngine();
        engine->setInputDevice(input_device_id, input_channel_count);
        engine->initFile();
    }
}

JNIEXPORT void JNICALL
Java_com_example_audiosave_AudioEngine_start(JNIEnv *env, jclass clazz) {
    if (engine == nullptr) {
        LOGE("Error starting audio engine, engine not created.");
    } else {
        if (!engine->start()) {
            LOGE("Error starting audio engine, engine failed to start.");
        }
    }
}

JNIEXPORT void JNICALL
Java_com_example_audiosave_AudioEngine_stop(JNIEnv *env, jclass clazz) {
    if (engine == nullptr) {
        LOGE("Error stopping audio engine, engine not created.");
    } else {
        engine->stop(); // blocking stop
    }
}

JNIEXPORT void JNICALL
Java_com_example_audiosave_AudioEngine_delete(JNIEnv *env, jclass clazz) {
    if (engine == nullptr) {
        LOGE("Error deleting audio engine, engine already deleted.");
    } else {
        engine->closeFile();
        delete engine;
        engine = nullptr;
    }
}

} // extern "C"