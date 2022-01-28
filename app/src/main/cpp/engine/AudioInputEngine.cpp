//
// Created by axk176431 on 4/7/2021.
//

#include <logging_macros.h>
#include "AudioInputEngine.h"

bool AudioInputEngine::start() {
    if (mStarted) {
        return true;
    }
    mStarted = true;

    // setup input stream parameters
    oboe::AudioStreamBuilder inBuilder;
    (&inBuilder)->setAudioApi(mAudioApi)
                ->setFormat(mFormat)
                ->setSharingMode(oboe::SharingMode::Exclusive)
                ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
                ->setDataCallback(this)
                ->setErrorCallback(this)
                ->setDeviceId(mInputDeviceId)
                ->setDirection(oboe::Direction::Input)
                ->setSampleRate(mSampleRate)
                ->setFramesPerDataCallback(mFramesPerBurst)
                ->setSampleRateConversionQuality(oboe::SampleRateConversionQuality::Fastest)
                ->setChannelCount(mInputChannelCount);
    oboe::Result result = inBuilder.openStream(mInputStream);

    // check if stream is setup properly
    if (result != oboe::Result::OK) {
        LOGE("Error setting up input stream parameters.");
        return false;
    }

    // warn if stream is not low latency
    if (mInputStream->getPerformanceMode() != oboe::PerformanceMode::LowLatency) {
        LOGW("Input stream is NOT low latency. "
             "Check input stream sample format, sample rate and channel count.");
    }

    // start input stream asynchronously
    mInputStream->requestStart();

    return true;
}

void AudioInputEngine::stop() {
    if (!mStarted) {
        return;
    }
    mStarted = false;
    oboe::Result result = mInputStream->stop();
    if (result != oboe::Result::OK) {
        LOGW("Error stopping stream: %s", oboe::convertToText(result));
    }
    result = mInputStream->close();
    if (result != oboe::Result::OK) {
        LOGE("Error closing stream: %s", oboe::convertToText(result));
    } else {
        LOGW("Successfully closed streams");
    }
    mInputStream.reset();
}

void AudioInputEngine::setSampleRate(int32_t sampleRate) {
    mSampleRate = sampleRate;
}

void AudioInputEngine::setInputDevice(int32_t id, int32_t channelCount) {
    mInputDeviceId = id;
    mInputChannelCount = channelCount;
}

oboe::DataCallbackResult
AudioInputEngine::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    if (!mStarted) {
        return oboe::DataCallbackResult::Stop;
    }
    onAudioInputReady(reinterpret_cast<float *>(audioData), numFrames);
    return oboe::DataCallbackResult::Continue;
}

void AudioInputEngine::onErrorBeforeClose(oboe::AudioStream * oboeStream, oboe::Result error) {
    LOGE("Input stream Error before close: %s", oboe::convertToText(error));
}

void AudioInputEngine::onErrorAfterClose(oboe::AudioStream * oboeStream, oboe::Result error) {
    LOGE("Input stream Error before close: %s", oboe::convertToText(error));
}

void AudioInputEngine::setFramesPerBurst(int32_t framesPerBurst) {
    mFramesPerBurst = framesPerBurst;
}

int32_t AudioInputEngine::getInputChannelCount() {
    return mInputChannelCount;
}


