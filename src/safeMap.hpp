#ifndef SAFEMAP_HPP
#define SAFEMAP_HPP

#include <unordered_map>
#include <mutex>

class SafeMap{
public:
    void set(unsigned int k, unsigned int val);
    unsigned int get(unsigned int k);
    unsigned int getSize();

private:
    std::unordered_map<unsigned int, unsigned int> piMap;
    std::mutex mtx;
};

#endif