# OS-Simulator

## Operating System Simulator

This project involves creating an operating system simulator with CPU scheduling, memory management, and disk management functionalities.

### CPU Scheduling

- Priority-based scheduling.
- Preemptive scheduling: Higher priority processes preempt lower priority ones.
- If multiple processes have the same highest priority, any of them can be scheduled.

### Memory Management

- Contiguous memory allocation.
- "Best-fit" approach: Allocate memory from the hole that best fits the process size.
- First-fit approach when multiple holes fit equally well.

### Disk Management

- First-come-first-served (FIFO) disk I/O queues.

### Structs

```cpp
struct FileReadRequest
{
    int PID{0};
    std::string fileName{""};
};

struct MemoryItem
{
    unsigned long long itemAddress;
    unsigned long long itemSize;
    int PID; // PID of the process using this chunk of memory
};

using MemoryUsage = std::vector<MemoryItem>;
```

### Class: SimOS
- Methods
    - SimOS(int numberOfDisks, unsigned long long amountOfRAM): Constructor to initialize the simulator with the number of disks and amount of RAM.

     - bool NewProcess(int priority, unsigned long long size): Create a new process with specified priority and memory size.

     - bool SimFork(): Fork a child process.

     - void SimExit(): Terminate the currently running process.

     - void SimWait(): Pause and wait for child processes to terminate.

     - void DiskReadRequest(int diskNumber, std::string fileName): Request to read a file from a disk.

     - void DiskJobCompleted(int diskNumber): Report completion of a disk job.

     - int GetCPU(): Get the PID of the process currently using the CPU.

     - std::vector<int> GetReadyQueue(): Get PIDs of processes in the ready-queue.

     - MemoryUsage GetMemory(): Get memory usage information.

     - FileReadRequest GetDisk(int diskNumber): Get information about the file read request for a specified disk.

     - std::queue<FileReadRequest> GetDiskQueue(int diskNumber): Get the I/O-queue of a specified disk.
 
# How to Run
   1. Clone this repository to your local machine.

   2. Open the test driver file (with main() function) in your preferred code editor.

   3. Build the project using the compilation command:

```cpp
    g++ -std=c++17 *.cpp -o runme
    
```
4. Run the executable:


```cpp
./runme

```

5. Review the output for correct simulation results.

Additional Notes
- Customize the test driver file to create and test scenarios.
- Ensure correct output by comparing it with expected results.
- For Linux compilation, use the provided command with the correct file names.


