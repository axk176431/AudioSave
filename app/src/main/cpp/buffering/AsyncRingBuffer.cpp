//
// Created by axk176431 on 6/23/2021.
//
#include "AsyncRingBuffer.h"

int32_t AsyncRingBuffer::read(float *readPtr, int32_t numFrames) {
    int32_t framesRead = 0;
    mMutex.lock();
    framesRead =  RingBuffer::read(readPtr, numFrames);
    mMutex.unlock();
    return framesRead;
}

int32_t AsyncRingBuffer::write(const float *writePtr, int32_t numFrames) {
    int32_t framesWritten = 0;
    mMutex.lock();
    framesWritten = RingBuffer::write(writePtr, numFrames);
    mMutex.unlock();
    return framesWritten;
}

bool AsyncRingBuffer::overlapRead(float *readPtr, int32_t numFrames, int32_t hopSize) {
    bool readSuccessful = false;
    mMutex.lock();
    readSuccessful = RingBuffer::overlapRead(readPtr, numFrames, hopSize);
    mMutex.unlock();
    return readSuccessful;
}

int32_t AsyncRingBuffer::getBufferSize() {
    int32_t bufferSize = 0;
    mMutex.lock();
    bufferSize = RingBuffer::getBufferSize();
    mMutex.unlock();
    return bufferSize;
}

int32_t AsyncRingBuffer::setBufferSize(int32_t bufferSize) {
    int32_t bufferSizeSet = 0;
    mMutex.lock();
    bufferSizeSet = RingBuffer::setBufferSize(bufferSize);
    mMutex.unlock();
    return bufferSize;
}

int32_t AsyncRingBuffer::getAvailableFrames() {
    int32_t availableFrames = 0;
    mMutex.lock();
    availableFrames = RingBuffer::getAvailableFrames();
    mMutex.unlock();
    return availableFrames;
}

bool AsyncRingBuffer::isFull() {
    bool isBufferFull = false;
    mMutex.lock();
    isBufferFull = RingBuffer::isFull();
    mMutex.unlock();
    return isBufferFull;
}



