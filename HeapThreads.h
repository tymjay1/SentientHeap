#ifndef HEAP_THREADS_H
#define HEAP_THREADS_H

#include "Heap.h"

#include <thread>
#include <random>
#include <chrono>
#include <iostream>

class HeapThreads {
    public:
        explicit HeapThreads(Heap* _heap) : heap(_heap) {}
        void startThreads();
        void joinThreads();

    private:
        void runGC();
        void runSocial();
        void runVisualizer();

        Heap* heap;
        std::thread gcThread, socialThread, visualizerThread;
};

#endif // HEAP_THREADS_H