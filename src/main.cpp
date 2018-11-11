#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <queue>
#include <mutex>
#include <unordered_map>

#include "computePi.hpp"
#include "safeQueue.hpp"
#include "safeMap.hpp"

#define NUMBER_OF_DIGITS 1000


void threadWorker(std::uint16_t threadNum, SafeQueue &piQueue, SafeMap &piMap) {
    while(piQueue.isEmpty() == false){
        unsigned int task = piQueue.pop();
        std::cout << ".";
        std::cout.flush();
        unsigned int piDigit = computePiDigit(task);
        piMap.set(task, piDigit);
    }
}

void showq(std::queue <int> q){
    std::queue <int> g = q;
    while(!g.empty()){
        std::cout << '\t' << g.front();
        g.pop();
    }
    std::cout << "\n";
}

void populateQueue(SafeQueue &piQueue){
    for(unsigned int i = 1; i <= NUMBER_OF_DIGITS; i++){
        piQueue.push(i);
    }
}


int main() {
    SafeQueue piQueue;
    populateQueue(piQueue);

    SafeMap piMap;

    //
    // Make as many threads as there are CPU cores
    // Assign them to run our threadWorker function, and supply arguments as necessary for that function
    std::vector<std::shared_ptr<std::thread>> threads;
    for (std::uint16_t core = 0; core < std::thread::hardware_concurrency(); core++)
        // The arguments you wish to pass to threadWorker are passed as
        // arguments to the constructor of std::thread
        threads.push_back(std::make_shared<std::thread>(threadWorker, core, std::ref(piQueue), std::ref(piMap)));

    //
    // Wait for all of these threads to complete
    for (auto&& thread : threads)
        thread->join();

    for(int i = 1; i <= piMap.getSize(); i++){
        std::cout << piMap.get(i);
    }

    return 0;
}