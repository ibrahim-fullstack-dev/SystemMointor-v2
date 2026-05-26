#include "readers/hardware/CPUReader.hpp"
#include "models/dal/hardware/CPURawModel.hpp" 

namespace System {

    namespace Reader {

        namespace Hardware {

           
            namespace CPUReader {

                bool FetchCPUSnapshot(Model::Hardware::DAL::CPU::stCPURawSnapshot& outSnapshot) {


                    outSnapshot.rawTicks.rawIdleTicks = 0;
                    outSnapshot.rawTicks.rawKernelTicks = 0;
                    outSnapshot.rawTicks.rawUserTicks = 0;
                    outSnapshot.rawTicks.rawInterruptTicks = 0;

                    outSnapshot.rawAnalytics.currentClockSpeedMhz = 0;
                    outSnapshot.rawAnalytics.activeCoreCount = 0;
                    outSnapshot.rawAnalytics.totalActiveProcesses = 0;
                    outSnapshot.rawAnalytics.totalActiveThreads = 0;

                    outSnapshot.snapshotTimestamp.rawSystemTimeTimestamp = 0;

                    return true; 
                }
            }


            namespace CoresReader {

                bool FetchCoreSnapshot(Model::Hardware::DAL::CPU::stCoreRawSnapshot& outSnapshot) {


                    for (size_t i = 0; i < Config::Limits::MAX_SUPPORTED_CORES; ++i) {
                        outSnapshot.rawCoreIdleTicks[i] = 0;
                        outSnapshot.rawCoreKernelTicks[i] = 0;
                        outSnapshot.rawCoreUserTicks[i] = 0;

                        outSnapshot.logicalIds[i] = static_cast<uint32_t>(i);
                        outSnapshot.coreTypes[i] = Enums::enCorePerformanceType::Unified;
                    }

                    outSnapshot.snapshotTimestamp.rawSystemTimeTimestamp = 0;
                    return true;
                }
            }

            namespace ProcessesReader {

                bool FetchProcessSnapshot(Model::Hardware::DAL::CPU::stProcessRawSnapshot& outSnapshot) {


                    for (size_t i = 0; i < Config::Limits::MAX_MONITORED_PROCESSES; ++i) {
                        outSnapshot.rawProcessKernelTicks[i] = 0;
                        outSnapshot.rawProcessUserTicks[i] = 0;
                        outSnapshot.processIds[i] = 0;


                        outSnapshot.processNames[i].fill('\0');
                    }

                    outSnapshot.snapshotTimestamp.rawSystemTimeTimestamp = 0;
                    return true;
                }
            }


            namespace ThreadsReader {

                bool FetchThreadSnapshot(Model::Hardware::DAL::CPU::stThreadRawSnapshot& outSnapshot) {


                    outSnapshot.parentProcessId = 0;
                    outSnapshot.activeThreadsCount = 0;

                    for (size_t i = 0; i < Config::Limits::MAX_MONITORED_THREADS; ++i) {
                        outSnapshot.threadIds[i] = 0;
                        outSnapshot.rawThreadKernelTicks[i] = 0;
                        outSnapshot.rawThreadUserTicks[i] = 0;
                    }

                    outSnapshot.snapshotTimestamp.rawSystemTimeTimestamp = 0;
                    return true;
                }
            }

        }
    }
}