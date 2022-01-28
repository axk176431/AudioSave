//
// Created by axk176431 on 1/27/2022.
//

#ifndef AUDIOSAVE_AUDIOSAVEENGINE_H
#define AUDIOSAVE_AUDIOSAVEENGINE_H

#include "AudioInputEngine.h"

static const char FILE_PATH[] = "sdcard/audioData.txt";

class AudioSaveEngine : public AudioInputEngine {

public:
    virtual void onAudioInputReady(float *audioData, int32_t numFrames) override;
    void initFile();
    void closeFile();

private:
    void writeToFile(float* data, int32_t numFrames);

    FILE *mFile = NULL;
};

#endif //AUDIOSAVE_AUDIOSAVEENGINE_H
