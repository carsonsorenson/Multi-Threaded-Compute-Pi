#include "safeQueue.hpp"

unsigned int SafeQueue::pop(){
    mtx.lock();
    int task = piQueue.front();
    piQueue.pop();
    mtx.unlock();
    return task;
}
void SafeQueue::push(int task){
    piQueue.push(task);
}

bool SafeQueue::isEmpty(){
    mtx.lock();
    bool empty = piQueue.empty();
    mtx.unlock();
    return empty;
}