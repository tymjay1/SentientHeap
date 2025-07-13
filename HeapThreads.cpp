#include "HeapThreads.h"

void HeapThreads::startThreads() {
    gcThread = std::thread(&HeapThreads::runGC, this);
    socialThread = std::thread(&HeapThreads::runSocial, this);
    visualizerThread = std::thread(&HeapThreads::runVisualizer, this);
}

void HeapThreads::joinThreads() {
    gcThread.join();
    socialThread.join();
    visualizerThread.join();
}

void HeapThreads::runGC() {
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        heap->sweep();
    }
}

void HeapThreads::runSocial() {
    std::random_device rd;
    std::mt19937 gen(rd());

    while(true) {
        auto blocks = heap->getBlocksSnapshot();
        if(blocks.size() < 2) continue;

        std::uniform_int_distribution<> dis(0, blocks.size() - 1);
        auto firstBlock = blocks[dis(gen)];
        auto secondBlock = blocks[dis(gen)];

        if(firstBlock != secondBlock) firstBlock->interact(secondBlock);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void HeapThreads::runVisualizer() {
    while(true) {
        auto blocks = heap->getBlocksSnapshot();
        std::cout << "\033[2J\033[H"; // Clear screen and move cursor top-left

        std::cout << "Sentient Heap:" << std::endl;
        for (const auto& b : blocks) {
            std::cout << "[" << b->getId() << "] Age: " << b->getAge() << " Links: ";
            for (auto& l : b->getLinks()) {
                if (auto ob = l.lock()) std::cout << ob->getId() << " ";
            }
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}