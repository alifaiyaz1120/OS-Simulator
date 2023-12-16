/*
    Name: Ali Faiyaz
    Class: CSCI 340 : OS Simulation Project
    Date: 05/14/2022

*/

#include <iostream>
#include "SimOS.h"

int SimOS::GetCPU() {
    return CPU_PID;

}
void SimOS::DiskReadRequest(int diskNumber, std::string fileName) {
 
    // Get the PID of the process currently using the CPU
    int currentPID = GetCPU();

    FileReadRequest request;
    request.PID = currentPID;
    request.fileName = fileName;

    if (CPU_PID == diskNumber + 1) {
        CPU_PID = 0;
    } else {
        // Update the CPU_PID based on the disk number
        CPU_PID = diskNumber + 1;
    }
    diskQueue[diskNumber].push(request);

    if (!readyQueue_.empty() && CheckMultiplePriorities() == true) { 
       CPU_PID = priority_counter;
       
    }
 
}

FileReadRequest SimOS::GetDisk( int diskNumber )
{
    // GetDisk returns an object with PID of the process served by specified disk and the name of the file read for that process. If the disk is idle, 
    // GetDisk returns the default FileReadRequest object (with PID 0 and empty string in fileName) 
    
    // check if the specified disk number is valid
    if (diskNumber >= numberOfDisks_ || diskNumber < 0) {
       // std::cout << "Invalid disk number." << std::endl;
        return FileReadRequest();
    }
    // Check if the disk is idle
    if (diskQueue[diskNumber].empty()) {
        return FileReadRequest();
    }
    // return the next read request in the disk queue
    return diskQueue[diskNumber].front();
}

std::queue<FileReadRequest> SimOS::GetDiskQueue(int diskNumber) {
    // GetDiskQueue returns the I/O-queue of the specified disk starting from the "next to be served" process.

    // check if the specified disk number is valid
    if (diskNumber >= numberOfDisks_ || diskNumber < 0) {
        //std::cout << "Invalid disk number." << std::endl;
        return std::queue<FileReadRequest>(); // Return an empty queue
    }
    std::queue<FileReadRequest>& ioQueue = diskQueue[diskNumber];
    std::queue<FileReadRequest> updatedQueue;
    // Remove and store the "next to be served" process from the I/O-queue
    if (!ioQueue.empty()) {
        updatedQueue.push(ioQueue.front());
        ioQueue.pop();
        
    }
    return ioQueue;
}

void SimOS::DiskJobCompleted(int diskNumber) {
       
    FileReadRequest disk = GetDisk(diskNumber);
    int diskPID = disk.PID;

    PID_counter++;

    // creating a new process with the incremented PID counter and the disk priority
    Process newProcess;
    newProcess.priority = diskPID;
    newProcess.PID = PID_counter;

    // Check if the current process in CPU is not 0
    if (CPU_PID != 0) {
        // compare the priorities 
        if (newProcess.priority > CPU_PID) {
    
            CPU_PID = newProcess.priority;
            newProcess.PID = CPU_PID;
            diskPID = 0;
        } 
    } else {
        CPU_PID++;
    }
    // update the disk PID 
    if (!diskQueue[diskNumber].empty()) {
       diskQueue[diskNumber].front().PID = diskPID;
    }

}

bool SimOS::CheckMultiplePriorities() {
    if (readyQueue_.size() <= 1) {
        return false;
    }
    // Check if there are multiple processes with the same priority
    int firstPriority = readyQueue_[0].priority;
    for (size_t i = 1; i < readyQueue_.size(); ++i) {
        if (readyQueue_[i].priority == firstPriority) {
            return true;
        }
    }
    return false;
}


