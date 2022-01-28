//
// Created by axk176431 on 6/23/2021.
//

#ifndef IVA_ASYNCRINGBUFFER_H
#define IVA_ASYNCRINGBUFFER_H

#include "RingBuffer.h"
#include <mutex>

class AsyncRingBuffer : public RingBuffer {

public:
    virtual int32_t read(float* readPtr, int32_t numFrames) override;
    virtual int32_t write(const float* writePtr, int32_t numFrames) override;
    virtual bool overlapRead(float* readPtr, int32_t numFrames, int32_t hopSize) override;
    virtual int32_t getBufferSize() override;
    virtual int32_t setBufferSize(int32_t bufferSize) override;
    virtual int32_t getAvailableFrames() override;
    virtual bool isFull() override;

private:
    std::mutex mMutex;
};

#endif //IVA_ASYNCRINGBUFFER_H
