#include "safeMap.hpp"

void SafeMap::set(unsigned int k, unsigned int val){
    mtx.lock();
    piMap[k] = val;
    mtx.unlock();
}

unsigned int SafeMap::get(unsigned int k){
    return piMap[k];
}

unsigned int SafeMap::getSize(){
    return piMap.size();
}