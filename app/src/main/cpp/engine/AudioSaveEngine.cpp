#include <logging_macros.h>
#include "AudioSaveEngine.h"

void AudioSaveEngine::onAudioInputReady(float *audioData, int32_t numFrames) {
    writeToFile(audioData, numFrames);
}

void AudioSaveEngine::initFile() {
    mFile = fopen(FILE_PATH, "w");
    if (mFile == NULL) {
        LOGE("Error while initializing file %s", FILE_PATH);
    }
}

void AudioSaveEngine::closeFile() {
    if (mFile != NULL) {
        fflush(mFile);
        fclose(mFile);
        mFile = NULL;
    }
}

void AudioSaveEngine::writeToFile(float *data, int32_t numFrames) {
    int32_t icc = getInputChannelCount();
    if (mFile != NULL) {
        for (int i = 0; i < numFrames; i++) {
            for (int j = 0; j < icc-1; j++) {
                fprintf(mFile, "%f,", data[i * icc + j]);
            }
            fprintf(mFile, "%f\r\n", data[i * icc + icc - 1]);
        }
    }
}
