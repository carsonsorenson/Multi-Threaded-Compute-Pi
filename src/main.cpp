#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <queue>
#include <mutex>
#include <unordered_map>
#include <fstream>
#include <string>

#include "computePi.hpp"
#include "safeQueue.hpp"
#include "safeMap.hpp"

#define NUMBER_OF_DIGITS 1000

void threadWorker(SafeQueue &piQueue, SafeMap &piMap) {
    while(piQueue.isEmpty() == false){
        unsigned int task = piQueue.pop();
        std::cout << ".";
        std::cout.flush();
        unsigned int piDigit = computePiDigit(task);
        piMap.set(task, piDigit);
    }
}

void populateQueue(SafeQueue &piQueue){
    for(unsigned int i = 1; i <= NUMBER_OF_DIGITS; i++){
        piQueue.push(i);
    }
}

void printPi(SafeMap &piMap){
    std::cout << "\n\n";
    std::cout << "3.";
    for(unsigned int i = 1; i <= piMap.getSize(); i++){
        std::cout << piMap.get(i);
    }
}

void prettyPi(SafeMap &piMap){
    std::vector<std::string> colors = {"\033[1;31m", "\033[1;33m", "\033[1;32m", "\033[1;34m", "\033[1;35m"};
    std::cout << "\n\n";
    std::ifstream infile("../pi.txt");
    std::string line;
    int index = -1;
    int lineCount = 0;
    while(infile >> line){
        int color = lineCount % colors.size();
        std::cout << colors[color];
        for(unsigned int i = 0; i < line.length(); i++){
            if (line[i] == '0'){
                std::cout << " ";
            }
            else{
                if(index == -1){
                    std::cout << "3";
                }
                else if (index == 0){
                    std::cout << ".";
                }
                else{
                    std::cout << piMap.get(index);
                }
                index++;
            }
        }
        std::cout << "\n";
        lineCount++;
    }
    infile.close();
    std::cout << "\n";
}


int main() {
    SafeQueue piQueue;
    populateQueue(piQueue);
    SafeMap piMap;

    std::vector<std::shared_ptr<std::thread>> threads;
    for (std::uint16_t core = 0; core < std::thread::hardware_concurrency(); core++){
        threads.push_back(std::make_shared<std::thread>(threadWorker, std::ref(piQueue), std::ref(piMap)));
    }

    for (auto&& thread : threads)
        thread->join();

    printPi(piMap);
    prettyPi(piMap);
    return 0;
}
