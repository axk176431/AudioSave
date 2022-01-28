//
// Created by axk176431 on 4/6/2021.
//

#include "RingBuffer.h"
#include <algorithm>

int32_t RingBuffer::read(float *readPtr, int32_t numFrames) {
    if (numFrames <= 0) {
        return 0;
    }
    int32_t framesRead = std::min(numFrames, mCount);
    for (int i = 0; i < framesRead; i++) {
        readPtr[i] = mData[(mHead + i) % mBufferSize];
    }
    mHead = (mHead + framesRead) % mBufferSize;
    mCount -= framesRead;
    return framesRead;
}

int32_t RingBuffer::write(const float *writePtr, int32_t numFrames) {
    int32_t framesWritten = std::min(numFrames, mBufferSize - mCount);
    for (int i = 0; i < framesWritten; i++) {
        mData[(mHead + mCount + i) % mBufferSize] = writePtr[i];
    }
    mCount += framesWritten;
    return framesWritten;
}

bool RingBuffer::overlapRead(float *readPtr, int32_t numFrames, int32_t hopSize) {
    if (numFrames <= 0 || numFrames > mCount) {
        return false;
    }
    for (int i = 0; i < numFrames; i++) {
        readPtr[i] = mData[(mHead + i) % mBufferSize];
    }
    mHead = (mHead + hopSize) % mBufferSize;
    mCount -= hopSize;
    return true;
}

int32_t RingBuffer::getBufferSize() {
    return mBufferSize;
}

int32_t RingBuffer::setBufferSize(int32_t bufferSize) {
    if (bufferSize < 0) {
        return mBufferSize;
    }
    mBufferSize = std::min(bufferSize, CAPACITY);
    return mBufferSize;
}

int32_t RingBuffer::getAvailableFrames() {
    return mCount;
}

bool RingBuffer::isFull() {
    return mCount == mBufferSize;
}
