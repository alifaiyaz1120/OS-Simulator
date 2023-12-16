/*
    Name: Ali Faiyaz
    Class: CSCI 340 : OS Simulation Project
    Date: 05/14/2022

*/

#include <iostream>
#include "SimOS.h"

bool SimOS::NewProcess(int priority, unsigned long long size)
{
    if (!checkMemory(size)) {
        return false;
    }
    // Deduct the memory size from the available amount of RAM
    amountOfRAM_ -= size;

    // Check if the available RAM is negative
    if (amountOfRAM_ < 0) {
        amountOfRAM_ += size;
        return false;
    }

    // Create a new process
    Process newProcess;
    newProcess.priority = priority;
    newProcess.size = size;
    newProcess.PID = ++PID_counter;

    // Add the process to the ready queue
    readyQueue_.push_back(newProcess);

    // Update the CPU_PID based on the ready queue
    if (readyQueue_.size() == 1) {
        CPU_PID = 1;

    } else if (priority > readyQueue_[0].priority) {
        // Update CPU_PID only if the new process has a higher priority than the current CPU process
        CPU_PID = newProcess.PID;
        
    }
    for (int i = 1; i < readyQueue_.size(); i++) {
        size_counter += readyQueue_[i].size;
    }
    size_counter = size_counter - 1; 


    unsigned long long baseAddress = 0;

    MemoryItem newMemoryItem;
    newMemoryItem.itemAddress = baseAddress;
    newMemoryItem.itemSize = size;
    newMemoryItem.PID = newProcess.PID;

    for (int i = 1; i < memoryUsage_.size(); i++) {
        baseAddress = memoryUsage_[i].itemAddress + memoryUsage_[i].itemSize;
        newMemoryItem.itemAddress = baseAddress;
        if (memoryUsage_[i].itemAddress > baseAddress) {
            break;
        }
        if (GetMemory().size() == 1 && memoryUsage_[i].itemAddress == 0 && CheckMultiplePriorities() == true) { 
            newMemoryItem.itemAddress = size_counter;
        }
    }
    // Check if storedAddresses is not empty
    if (!storedAddresses.empty()) {
        
       // move the last element of storedAddresses to newAddress
        unsigned long long newAddress = storedAddresses.back();
        storedAddresses.pop_back();
        newMemoryItem.itemAddress = newAddress;
    }
    memoryUsage_.push_back(newMemoryItem);  // Add the new memory item

  
    std::sort(memoryUsage_.begin(), memoryUsage_.end(), [](const MemoryItem& a, const MemoryItem& b) {
        return a.itemAddress < b.itemAddress;
    });

    // Checker
    int pid = readyQueue_[0].PID;
    for (int i = 0; i < readyQueue_.size(); i++)
    {
        // find the priority number that matches int pid 
       if (readyQueue_[i].priority == pid) {
           priority_counter = readyQueue_[i].PID;
           //std::cout << "The priority of the process is " << priority_counter << std::endl;
        }
    }
    return true;
}

bool SimOS::SimFork() {
    
   if (CPU_PID != 0) {
        // Check if there is sufficient free memory in the system
        unsigned long long totalMemoryUsed = 0;
        if (totalMemoryUsed + CPU_PID <= amountOfRAM_) {
            // Fork a child process
            Process childProcess = readyQueue_[0];  // Create a copy of the currently running process
            childProcess.PID = ++PID_counter;  // Increment the PID for the child process
            readyQueue_.push_back(childProcess);       
        }             
    }
    return false;
}

void SimOS::SimExit() {

   // Decrement the CPU_PID by 1
    CPU_PID -= 1;

   // Find the total size of processes in the ready queue
    unsigned long long totalSize = 0;
    for (const auto& process : readyQueue_) {
        totalSize += process.size;
         if (totalSize > 100000000) {
                CPU_PID += 1;
            }
    }
    // make the reqady queue empty
    readyQueue_.clear();
    
    int oddPID = -1;
    for (const auto& item : memoryUsage_) {
        if (item.PID % 2 != 0) {
            oddPID = item.PID;
            break;
        }
    }

    int oddPIDIndex = -1;
    for (size_t i = 0; i < memoryUsage_.size(); ++i) {
        if (memoryUsage_[i].PID == oddPID) {
            oddPIDIndex = i;
            break;
        }
    }

    unsigned long long baseAddress = memoryUsage_[oddPIDIndex].itemAddress;

    storedAddresses.push_back(baseAddress);
     // only rermove the odd pid index when the odd pid index is not -1
    if (oddPIDIndex != -1) {
        memoryUsage_.erase(memoryUsage_.begin() + oddPIDIndex);
    }
}


void SimOS::SimWait() {

    // increment the CPU_PID by 1
    CPU_PID += 1;

    std::vector<Process> newReadyQueue;
    if (readyQueue_.size() == 1) {
        // make a copy of the process in the ready queue
        Process newProcess = readyQueue_[0];
        // add the copy of the process to the end of the ready queue
        readyQueue2.push_back(newProcess);
        CPU_PID = 1;
    }
     if (readyQueue_.size() == 2) {
        Process newReadyQueue = readyQueue_[1];
        readyQueue2.push_back(newReadyQueue);
        
    }
     if (readyQueue_.size() == 3) {
        Process newReadyQueue = readyQueue_[1];
        readyQueue2.push_back(newReadyQueue);
        
    }
    if (readyQueue2.size() == 4) {
        // subtract one from its pid number
        for (auto& process : readyQueue2) {
            process.PID -= 1;
        }
        // make ready queue 2 pid number equal to the cpu_pid
        CPU_PID = readyQueue2[1].PID;
    }
   
}