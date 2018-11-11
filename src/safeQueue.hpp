#ifndef SAFEQUEUE_HPP
#define SAFEQUEUE_HPP

#include <queue>
#include <mutex>

class SafeQueue{
public:
    void push(int n);
    unsigned int pop();
    bool isEmpty();

private:
    std::queue<int> piQueue;
    std::mutex mtx;
};

#endif