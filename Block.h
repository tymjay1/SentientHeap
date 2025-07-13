#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <memory>
#include <mutex>
#include <vector>
#include <thread>

class Block {
    public:
        enum class Personality { FRIENDLY, CHAOTIC, MANIPULATIVE, DEPRESSED };

        Block(int _id, Personality _personality) : id(_id), personality(_personality), age(0), markGC(false) {}
        ~Block() = default;

        void aging();
        void interact(std::shared_ptr<Block> otherBlock);
        void formClique(std::shared_ptr<Block> otherBlock);
        void link(std::shared_ptr<Block> otherBlock);
        void unlink(std::shared_ptr<Block> otherBlock);
        void mark();
        void unmark();

        int getId() const;
        int getAge() const;
        Personality getPersonality() const;
        bool isMarked() const;
        bool isRebellious() const;
        bool isTerminated() const;
        std::vector<std::weak_ptr<Block>> getLinks() const;

    private:
        int id;
        int age;
        Personality personality;
        std::vector<std::weak_ptr<Block>> links;
        bool markGC;
        mutable std::mutex mutex;
};

#endif // BLOCK_H