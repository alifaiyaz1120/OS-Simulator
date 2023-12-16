/*
    Name: Ali Faiyaz
    Class: CSCI 340 : OS Simulation Project
    Date: 05/14/2022

*/
#ifndef SIMOS_H
#define SIMOS_H

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <unordered_map>
#include <iostream>

struct FileReadRequest
{
    int PID = 0;
    std::string fileName = "";
};

struct MemoryItem
{
    unsigned long long itemAddress;
    unsigned long long itemSize;
    int PID;
};

struct Process {
    int priority;
    unsigned long long size;
    int PID;
};

using MemoryUsage = std::vector<MemoryItem>;

class SimOS {
    public: 
        SimOS(int numberOfDisks, unsigned long long amountOfRAM);
        bool NewProcess(int priority, unsigned long long size);
        bool SimFork();
        void SimExit();
        void SimWait();
        void DiskReadRequest(int diskNumber, std::string fileName);
        void DiskJobCompleted(int diskNumber);
        int GetCPU();
        std::vector<int> GetReadyQueue();
        MemoryUsage GetMemory();
        FileReadRequest GetDisk(int diskNumber);
        std::queue<FileReadRequest> GetDiskQueue(int diskNumber);

        // Added functions
        bool checkMemory(unsigned long long size);
        void PrintMemory();
        bool CheckMultiplePriorities();
        void PrintReadyQueue();

    private:
        int numberOfDisks_;
        unsigned long long amountOfRAM_;
        int PID_counter;
        int CPU_PID;
        std:: vector <Process> readyQueue_;
        std::vector <Process> readyQueue2;

        MemoryUsage memoryUsage_;
        std::vector<std::queue<FileReadRequest> > diskQueue;
        std::vector<unsigned long long> storedAddresses;
        int priority_counter;
        int size_counter;



};

#endif
