//
// Created by axk176431 on 4/7/2021.
//

#ifndef AUDIOSAVE_AUDIOINPUTENGINE_H
#define AUDIOSAVE_AUDIOINPUTENGINE_H

#include <oboe/Oboe.h>

class AudioInputEngine : public oboe::AudioStreamCallback {

public:
    virtual bool start();
    virtual void stop();
    void setSampleRate(int32_t sampleRate);
    void setInputDevice(int32_t id, int32_t channelCount);
    void setFramesPerBurst(int32_t framesPerBurst);
    int32_t getInputChannelCount();

    // callbacks
    virtual void onAudioInputReady(float *audioData, int32_t numFrames) = 0;
    oboe::DataCallbackResult onAudioReady (oboe::AudioStream *audioStream,
            void *audioData, int32_t numFrames) override;
    void onErrorBeforeClose (oboe::AudioStream *, oboe::Result) override;
    void onErrorAfterClose (oboe::AudioStream *, oboe::Result) override;

private:
    bool mStarted;
    int32_t mInputDeviceId = oboe::kUnspecified;
    const oboe::AudioFormat mFormat = oboe::AudioFormat::Float;
    oboe::AudioApi mAudioApi = oboe::AudioApi::AAudio;
    int32_t mSampleRate = oboe::kUnspecified;
    int32_t mInputChannelCount = oboe::ChannelCount::Mono;
    int32_t mFramesPerBurst = oboe::kUnspecified;

    std::shared_ptr<oboe::AudioStream> mInputStream;
};

#endif //IVA_AUDIOINPUTENGINE_H
