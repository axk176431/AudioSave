//
// Created by axk176431 on 4/6/2021.
//

#ifndef IVA_RINGBUFFER_H
#define IVA_RINGBUFFER_H

#include <oboe/Oboe.h>

const int32_t CAPACITY = 2048;

class RingBuffer {

public:

    virtual int32_t read(float* readPtr, int32_t numFrames);
    virtual int32_t write(const float* writePtr, int32_t numFrames);
    virtual bool overlapRead(float* readPtr, int32_t numFrames, int32_t hopSize);
    virtual int32_t getBufferSize();
    virtual int32_t setBufferSize(int32_t bufferSize);
    virtual int32_t getAvailableFrames();
    virtual bool isFull();

private:
    int32_t mHead = 0;
    int32_t mCount = 0;
    int32_t mBufferSize = CAPACITY;
    float mData[CAPACITY];
};

#endif //IVA_RINGBUFFER_H
