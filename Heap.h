#ifndef HEAP_H
#define HEAP_H

#include "Block.h"

#include <iostream>
#include <memory>
#include <mutex>
#include <vector>
#include <thread>

class Heap {
    public:
        std::shared_ptr<Block> allocateBlock(Block::Personality p);
        void update();
        void feed();
        void sweep();

        std::vector<std::shared_ptr<Block>> getBlocksSnapshot() const;

    private:
        int nextId = 0;
        std::vector<std::shared_ptr<Block>> blocks;
        int feedLevel = 100;
        mutable std::mutex mutex;
};

#endif // HEAP_H