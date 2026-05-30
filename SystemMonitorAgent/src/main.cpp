#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <vector>

#include "models/dal/hardware/CPURawModel.hpp"
#include "readers/hardware/CPUReader.hpp"

void PrintSectionHeader(const std::string title) {
    std::cout << "\n==================================================\n";
    std::cout << " Testing: " << title << "\n";
    std::cout << "==================================================\n";
}

void CPU() {

    PrintSectionHeader("CPUReader::FetchCPUSnapshot");

    System::Model::Raw::CPU::stCPURawSnapshot cpuSnapshot;
    System::Reader::CPU::CPUReader reader;

    if (reader.FetchCPUTicks(cpuSnapshot)) {
        std::cout << "  -> Raw Idle Ticks          : " << cpuSnapshot.dynamicAnalytics.rawTicks.rawIdleTicks << "\n";
        std::cout << "  -> Raw Kernel Ticks        : " << cpuSnapshot.dynamicAnalytics.rawTicks.rawKernelTicks << "\n";
        std::cout << "  -> Raw User Ticks          : " << cpuSnapshot.dynamicAnalytics.rawTicks.rawUserTicks << "\n";
        std::cout << "  -> Raw Interrupt Ticks     : " << cpuSnapshot.dynamicAnalytics.rawTicks.rawInterruptTicks << "\n";

    }
    else {
        std::cerr << "[FAILURE] FetchCPUTicks failed!\n";
    }

    if(reader.FetchDynamicAnalytics(cpuSnapshot))
    {
        std::cout << "  -> Active Process Count    : " << cpuSnapshot.dynamicAnalytics.totalActiveProcesses << "\n";
        std::cout << "  -> Active Thread Count     : " << cpuSnapshot.dynamicAnalytics.totalActiveThreads << "\n";
        std::cout << "  -> Active Handle Count     : " << cpuSnapshot.dynamicAnalytics.totalOpenedHandles << "\n";

        std::cout << "  -> Snapshot Timestamp      : " << cpuSnapshot.dynamicAnalytics.snapshotTimestamp.rawSystemTimeTimestamp << "\n";

    }
    else {
        std::cerr << "[FAILURE] FetchDynamicAnalytics failed!\n";
    }

    if (reader.FetchStaticAnalytics(cpuSnapshot)) {

        std::wcout << "  -> Processor Architecture  : " << (cpuSnapshot.staticAnalytics.ProcessorArchitecture.data()) << "\n";
        std::wcout << "  -> Processor Name String   : " << (cpuSnapshot.staticAnalytics.ProcessorNameString.data()) << "\n";
    }
    else {
        std::cerr << "[FAILURE] FetchStaticAnalytics failed!\n";
    }

}

//void Cores() {
//
//    PrintSectionHeader("CoresReader::FetchCoreSnapshot");
//
//    System::Model::Hardware::DAL::CPU::stCoreRawSnapshot coreSnapshot;
//
//    bool coreResult = System::Reader::Hardware::CoresReader::FetchCoreSnapshot(coreSnapshot);
//
//    if (coreResult) {
//        std::cout << "[SUCCESS] FetchCoreSnapshot returned true.\n";
//        std::cout << "  -> Max Supported Cores : " << System::Config::Limits::MAX_SUPPORTED_CORES << "\n";
//
//
//        for (size_t i = 0; i < 2 && i < System::Config::Limits::MAX_SUPPORTED_CORES; ++i) {
//            std::cout << "  -> Core [" << i << "] Logical ID : " << coreSnapshot.logicalIds[i]
//                << " | Type ID: " << static_cast<int>(coreSnapshot.coreTypes[i])
//                << " | Idle Ticks: " << (coreSnapshot.rawCoreIdleTicks[i])
//                << " | Kernel Ticks: " << (coreSnapshot.rawCoreKernelTicks[i])
//                << " | User Ticks: " << (coreSnapshot.rawCoreUserTicks[i]) << "\n";
//        }
//        std::cout << "  -> Snapshot Timestamp  : " << coreSnapshot.snapshotTimestamp.rawSystemTimeTimestamp << "\n";
//    }
//    else {
//        std::cerr << "[FAILURE] FetchCoreSnapshot failed!\n";
//    }
//}
//
//void Processes() {
//
//    PrintSectionHeader("ProcessesReader::FetchProcessSnapshot");
//
//    System::Model::Hardware::DAL::CPU::stProcessRawSnapshot processSnapshot;
//
//    bool processResult = System::Reader::Hardware::ProcessesReader::FetchProcessSnapshot(processSnapshot);
//
//    if (processResult) {
//        std::cout << "[SUCCESS] FetchProcessSnapshot returned true.\n";
//        std::cout << "  -> Max Monitored Proc  : " << System::Config::Limits::MAX_MONITORED_PROCESSES << "\n";
//
//        for (size_t i = 0; i < 2 && i < System::Config::Limits::MAX_MONITORED_PROCESSES; ++i) {
//            std::cout << "  -> Process [" << i << "] Logical ID : " << processSnapshot.processIds[i]
//                << " | Name: " << i
//                << " | Kernel Ticks: " << (processSnapshot.rawProcessKernelTicks[i])
//                << " | User Ticks: " << (processSnapshot.rawProcessUserTicks[i]) << "\n";
//        }
//
//        std::cout << "  -> Snapshot Timestamp  : " << processSnapshot.snapshotTimestamp.rawSystemTimeTimestamp << "\n";
//    }
//    else {
//        std::cerr << "[FAILURE] FetchProcessSnapshot failed!\n";
//    }
//
//}
//
//void Threads() {
//
//    PrintSectionHeader("ThreadsReader::FetchThreadSnapshot");
//
//    System::Model::Hardware::DAL::CPU::stThreadRawSnapshot threadSnapshot;
//
//    bool threadResult = System::Reader::Hardware::ThreadsReader::FetchThreadSnapshot(threadSnapshot);
//
//    if (threadResult) {
//        std::cout << "[SUCCESS] FetchThreadSnapshot returned true.\n";
//        std::cout << "  -> Max Monitored Threads: " << System::Config::Limits::MAX_MONITORED_THREADS << "\n";
//        std::cout << "  -> Parent Process ID    : " << threadSnapshot.parentProcessId << "\n";
//        std::cout << "  -> Active Threads Count : " << threadSnapshot.activeThreadsCount << "\n";
//
//        for (size_t i = 0; i < 2 && i < System::Config::Limits::MAX_MONITORED_THREADS; ++i) {
//            std::cout << "  -> Thread [" << i << "] Logical ID : " << threadSnapshot.threadIds[i]
//                << " | Kernel Ticks: " << (threadSnapshot.rawThreadKernelTicks[i])
//                << " | User Ticks: " << (threadSnapshot.rawThreadUserTicks[i]) << "\n";
//        }
//    }
//    else {
//        std::cerr << "[FAILURE] FetchThreadSnapshot failed!\n";
//    }
//}

int main() {
    std::cout << "?? Starting Data Access Layer (DAL) Integration Test...\n";

    CPU();

    return 0;
}

