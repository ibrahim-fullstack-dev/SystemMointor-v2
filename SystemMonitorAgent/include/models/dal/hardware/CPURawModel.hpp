#pragma once
#include <array>
#include <cstdint>
#include "config/SystemLimits.hpp"
#include "models/dal/RawCommon.hpp"
#include "enums/EnumsProvider.hpp"

namespace System {

    namespace Models {

        namespace Raw {

            namespace CPU {

                // Interface raw counters (serves stInterfaceCounters)
                struct stCPURawTicks
                {
                    uint64_t rawIdleTicks = 0;
                    uint64_t rawKernelTicks = 0;
                    uint64_t rawUserTicks = 0;
                    uint64_t rawInterruptTicks = 0;
                };

                // Static info.
                struct stCPUStaticRawAnalytics
                {
                    std::array<wchar_t, 16>  ProcessorArchitecture{};
                    std::array<wchar_t, 128> ProcessorNameString{};
                    uint32_t activeCoreCount = 0;
                    uint32_t currentClockSpeedMhz = 0;
                };

                // Update inside loop
                struct stCPUDynamicRawAnalytics
                {
                    stCPURawTicks rawTicks;
                    uint32_t totalActiveProcesses = 0;
                    uint32_t totalActiveThreads = 0;
                    uint32_t totalOpenedHandles = 0;

                    stTimestamp snapshotTimestamp;
                };

                // 3. The complete raw snapshot for CPU (serves stCPUDTO)
                struct stCPURawSnapshot
                {
                    stCPUStaticRawAnalytics  staticAnalytics;
                    stCPUDynamicRawAnalytics dynamicAnalytics;
                };

                // 2. Core raw counters (serves stCoreDTO)
                struct stCoreRawSnapshot
                {
                    std::array<uint64_t, Config::Limits::MAX_SUPPORTED_CORES> rawCoreIdleTicks{};
                    std::array<uint64_t, Config::Limits::MAX_SUPPORTED_CORES> rawCoreKernelTicks{};
                    std::array<uint64_t, Config::Limits::MAX_SUPPORTED_CORES> rawCoreUserTicks{};

                    std::array<uint32_t, Config::Limits::MAX_SUPPORTED_CORES> logicalIds{};
                    std::array<Enums::enCorePerformanceType, Config::Limits::MAX_SUPPORTED_CORES> coreTypes{};

                    stTimestamp snapshotTimestamp;
                };

                // 3. Process raw counters (serves stProcessDTO)
                struct stProcessRawSnapshot
                {
                    std::array<uint64_t, Config::Limits::MAX_MONITORED_PROCESSES> rawProcessKernelTicks{};
                    std::array<uint64_t, Config::Limits::MAX_MONITORED_PROCESSES> rawProcessUserTicks{};

                    std::array<uint32_t, Config::Limits::MAX_MONITORED_PROCESSES> processIds{};
                    std::array<std::array<char, 32>, Config::Limits::MAX_MONITORED_PROCESSES> processNames{};

                    stTimestamp snapshotTimestamp;
                };

                // 4. Thread raw counters (serves stThreadDTO)
                struct stThreadRawSnapshot
                {
                    uint32_t parentProcessId = 0;
                    uint32_t activeThreadsCount = 0;

                    std::array<uint32_t, Config::Limits::MAX_MONITORED_THREADS> threadIds{};
                    std::array<uint64_t, Config::Limits::MAX_MONITORED_THREADS> rawThreadKernelTicks{};
                    std::array<uint64_t, Config::Limits::MAX_MONITORED_THREADS> rawThreadUserTicks{};

                    stTimestamp snapshotTimestamp;
                };

            }
        }
    }
}