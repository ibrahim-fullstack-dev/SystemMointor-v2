#include <iostream>
#include <iomanip>
#include <cassert>

#include "models/dal/hardware/CPURawModel.hpp"
#include "readers/hardware/CPUReader.hpp"

void CPU() {

    PrintSectionHeader("CPUReader::FetchCPUSnapshot");

    System::Model::Hardware::DAL::CPU::stCPURawSnapshot cpuSnapshot;


    bool cpuResult = System::Reader::Hardware::CPUReader::FetchCPUSnapshot(cpuSnapshot);

    if (cpuResult) {
        std::cout << "[SUCCESS] FetchCPUSnapshot returned true.\n";
        std::cout << "  -> Raw Idle Ticks      : " << cpuSnapshot.rawTicks.rawIdleTicks << "\n";
        std::cout << "  -> Raw Kernel Ticks    : " << cpuSnapshot.rawTicks.rawKernelTicks << "\n";
        std::cout << "  -> Raw User Ticks    : " << cpuSnapshot.rawTicks.rawUserTicks << "\n";
        std::cout << "  -> Raw Interrupt Ticks    : " << cpuSnapshot.rawTicks.rawInterruptTicks << "\n";

        std::cout << "  -> Clock Speed         : " << cpuSnapshot.rawAnalytics.currentClockSpeedMhz << " MHz\n";
        std::cout << "  -> Active Core Count   : " << cpuSnapshot.rawAnalytics.activeCoreCount << "\n";
        std::cout << "  -> Active Process Count   : " << cpuSnapshot.rawAnalytics.totalActiveProcesses << "\n";
        std::cout << "  -> Active Thread Count   : " << cpuSnapshot.rawAnalytics.totalActiveThreads << "\n";

        std::cout << "  -> Snapshot Timestamp  : " << cpuSnapshot.snapshotTimestamp.rawSystemTimeTimestamp << "\n";
    }
    else {
        std::cerr << "[FAILURE] FetchCPUSnapshot failed!\n";
    }



}

void Cores() {

    PrintSectionHeader("CoresReader::FetchCoreSnapshot");

    System::Model::Hardware::DAL::CPU::stCoreRawSnapshot coreSnapshot;

    bool coreResult = System::Reader::Hardware::CoresReader::FetchCoreSnapshot(coreSnapshot);

    if (coreResult) {
        std::cout << "[SUCCESS] FetchCoreSnapshot returned true.\n";
        std::cout << "  -> Max Supported Cores : " << System::Config::Limits::MAX_SUPPORTED_CORES << "\n";


        for (size_t i = 0; i < 2 && i < System::Config::Limits::MAX_SUPPORTED_CORES; ++i) {
            std::cout << "  -> Core [" << i << "] Logical ID : " << coreSnapshot.logicalIds[i]
                << " | Type ID: " << static_cast<int>(coreSnapshot.coreTypes[i])
                << " | Idle Ticks: " << (coreSnapshot.rawCoreIdleTicks[i])
                << " | Kernel Ticks: " << (coreSnapshot.rawCoreKernelTicks[i])
                << " | User Ticks: " << (coreSnapshot.rawCoreUserTicks[i]) << "\n";
        }
        std::cout << "  -> Snapshot Timestamp  : " << coreSnapshot.snapshotTimestamp.rawSystemTimeTimestamp << "\n";
    }
    else {
        std::cerr << "[FAILURE] FetchCoreSnapshot failed!\n";
    }
}

void Processes() {

    PrintSectionHeader("ProcessesReader::FetchProcessSnapshot");

    System::Model::Hardware::DAL::CPU::stProcessRawSnapshot processSnapshot;

    bool processResult = System::Reader::Hardware::ProcessesReader::FetchProcessSnapshot(processSnapshot);

    if (processResult) {
        std::cout << "[SUCCESS] FetchProcessSnapshot returned true.\n";
        std::cout << "  -> Max Monitored Proc  : " << System::Config::Limits::MAX_MONITORED_PROCESSES << "\n";

        for (size_t i = 0; i < 2 && i < System::Config::Limits::MAX_MONITORED_PROCESSES; ++i) {
            std::cout << "  -> Core [" << i << "] Logical ID : " << processSnapshot.processIds[i]
                << " | Name: " << (processSnapshot.processNames[i])
                << " | Kernel Ticks: " << (processSnapshot.rawProcessKernelTicks[i])
                << " | User Ticks: " << (processSnapshot.rawProcessUserTicks[i]) << "\n";
        }

        std::cout << "  -> Snapshot Timestamp  : " << processSnapshot.snapshotTimestamp.rawSystemTimeTimestamp << "\n";
    }
    else {
        std::cerr << "[FAILURE] FetchProcessSnapshot failed!\n";
    }

}

void Threads() {

    PrintSectionHeader("ThreadsReader::FetchThreadSnapshot");

    System::Model::Hardware::DAL::CPU::stThreadRawSnapshot threadSnapshot;

    bool threadResult = System::Reader::Hardware::ThreadsReader::FetchThreadSnapshot(threadSnapshot);

    if (threadResult) {
        std::cout << "[SUCCESS] FetchThreadSnapshot returned true.\n";
        std::cout << "  -> Max Monitored Threads: " << System::Config::Limits::MAX_MONITORED_THREADS << "\n";
        std::cout << "  -> Parent Process ID    : " << threadSnapshot.parentProcessId << "\n";
        std::cout << "  -> Active Threads Count : " << threadSnapshot.activeThreadsCount << "\n";

        for (size_t i = 0; i < 2 && i < System::Config::Limits::MAX_MONITORED_THREADS; ++i) {
            std::cout << "  -> Core [" << i << "] Logical ID : " << threadSnapshot.threadIds[i]
                << " | Kernel Ticks: " << (threadSnapshot.rawThreadKernelTicks[i])
                << " | User Ticks: " << (threadSnapshot.rawThreadUserTicks[i]) << "\n";
        }
    }
    else {
        std::cerr << "[FAILURE] FetchThreadSnapshot failed!\n";
    }
}

void PrintSectionHeader(const std::string title) {
    std::cout << "\n==================================================\n";
    std::cout << " ?? Testing: " << title << "\n";
    std::cout << "==================================================\n";
}

int main() {
    std::cout << "?? Starting Data Access Layer (DAL) Integration Test...\n";

    CPU();

    return 0;
}

