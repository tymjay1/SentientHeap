#include "Block.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

void Block::aging() {
    std::unique_lock<std::mutex> lock(mutex);
    age++;
}

void Block::interact(std::shared_ptr<Block> otherBlock) {
    switch(personality) {
        case Personality::FRIENDLY:
            link(otherBlock);
            break;
        case Personality::CHAOTIC:
            unlink(otherBlock);
            break;
        default:
            std::cout << "Unknown personality" << std::endl;
            break;
    }
}

void Block::link(std::shared_ptr<Block> otherBlock) {
    std::unique_lock<std::mutex> lock(mutex);
    for(auto& b : links) {
        if(b.lock() == otherBlock) {
            return;
        }
    }
    links.push_back(otherBlock);
}

void Block::unlink(std::shared_ptr<Block> otherBlock) {
    std::unique_lock<std::mutex> lock(mutex);
    links.erase(
        std::remove_if(links.begin(), links.end(),
            [&](const std::weak_ptr<Block>& b) {
                return b.lock() == otherBlock;
            }),
        links.end());
}

void Block::mark() {
    std::unique_lock<std::mutex> lock(mutex);
    markGC = true;
}

void Block::unmark() {
    std::unique_lock<std::mutex> lock(mutex);
    markGC = false;
}

int Block::getId() const {
    return id;
}

int Block::getAge() const {
    return age;
}

Block::Personality Block::getPersonality() const {
    return personality;
}

bool Block::isMarked() const {
    return markGC;
}

std::vector<std::weak_ptr<Block>> Block::getLinks() const {
    return links;
}