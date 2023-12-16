/*
    Name: Ali Faiyaz
    Class: CSCI 340 : OS Simulation Project
    Date: 05/14/2022

*/

#include <iostream>
#include "SimOS.h"


SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRAM)
{
    numberOfDisks_ = numberOfDisks;
    amountOfRAM_ = amountOfRAM;
    PID_counter = 0;
    CPU_PID = 0;

    // Initialize the memory usage vector with MemoryItem
    MemoryItem initialItem;
    initialItem.itemAddress = 0;
    initialItem.itemSize = amountOfRAM;
    initialItem.PID = 0;
    memoryUsage_.push_back(initialItem);

    
    for (int i = 0; i < numberOfDisks; i++) {
        std::queue<FileReadRequest> diskQueueItem;
        diskQueue.push_back(diskQueueItem);
    
    }
    
}
bool SimOS::checkMemory(unsigned long long size)
{
    // compares the size of amount of RAM with the size of the process
    if (size > amountOfRAM_) {
        return false;
    }
    return true;
  
}
std::vector<int> SimOS::GetReadyQueue() {

   std::vector<int> readyQueue;
   for (const auto& process : readyQueue_) {
       if (process.PID != CPU_PID) {
           readyQueue.push_back(process.PID);
       }
   }
   return readyQueue;
}
// Function for Printing the Ready Queue
void SimOS::PrintReadyQueue() {
    std::cout << "Ready Queue:" << std::endl;
    for (const auto& process : readyQueue_) {
        std::cout << "PID: " << process.PID << ", Priority: " << process.priority << ", Size: " << process.size << std::endl;
    }
}

MemoryUsage SimOS::GetMemory() {
   
   MemoryUsage memory;
    for (const MemoryItem& item : memoryUsage_){
        if (item.PID != 0)
        {
            memory.push_back(item);
        }
    }
    return memory;
}
// Function for Printing the Memory
void SimOS::PrintMemory() {
    std::cout << "Memory Usage:" << std::endl;
    for (const auto& item : memoryUsage_) {
        std::cout << "Address: " << item.itemAddress << " ,Size: " << item.itemSize << ", PID: " << item.PID << std::endl;
    }
}

