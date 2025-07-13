#include "Heap.h"

#include <algorithm>

std::shared_ptr<Block> Heap::allocateBlock(Block::Personality p) {
    std::unique_lock<std::mutex> lock(mutex);
    auto newBlock = std::make_shared<Block>(++nextId, p);
    blocks.push_back(newBlock);
    return newBlock;
}

void Heap::update() {
    std::unique_lock<std::mutex> lock(mutex);
    for(auto& b : blocks) {
        b->aging();
    }
}

void Heap::sweep() {
    std::unique_lock<std::mutex> lock(mutex);
    blocks.erase(
        std::remove_if(blocks.begin(), blocks.end(),
            [&](const std::shared_ptr<Block>& b) {
                return b.use_count() <= 1;
            }),
        blocks.end());
}

std::vector<std::shared_ptr<Block>> Heap::getBlocksSnapshot() const {
    return blocks;
}