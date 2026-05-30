#include "readers/hardware/CPUReader.hpp"
#include "utils/WinTimeUtils.hpp"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include<psapi.h>
#include <cstring>
#include <cstdint>

namespace System {

    namespace Reader {

        namespace CPU {

            bool CPUReader::FetchStaticAnalytics(Model::Raw::CPU::stCPURawSnapshot& outSnapshot) {
                // Fetch Cores and Architecture
                SYSTEM_INFO sysInfo;
                GetSystemInfo(&sysInfo);
                outSnapshot.staticAnalytics.activeCoreCount = sysInfo.dwNumberOfProcessors;

                // Fetch Processor Architecture
                const wchar_t* archText = L"Unknown";
                switch (sysInfo.wProcessorArchitecture) {
                case PROCESSOR_ARCHITECTURE_AMD64: archText = L"x64";    break;
                case PROCESSOR_ARCHITECTURE_ARM64: archText = L"ARM64";  break;
                case PROCESSOR_ARCHITECTURE_INTEL: archText = L"x86";    break;
                }

                wcscpy_s(outSnapshot.staticAnalytics.ProcessorArchitecture.data(),
                    outSnapshot.staticAnalytics.ProcessorArchitecture.size(),
                    archText);

                // Fetch Processor name and frequency from Registry
                DWORD mhzSpeed = 0;
                DWORD dataSize = sizeof(mhzSpeed);
                RegGetValueW(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", L"~MHz", RRF_RT_REG_DWORD, NULL, &mhzSpeed, &dataSize);
                outSnapshot.staticAnalytics.currentClockSpeedMhz = static_cast<uint32_t>(mhzSpeed);

                DWORD stringBufferSizeBytes = static_cast<DWORD>(outSnapshot.staticAnalytics.ProcessorNameString.size() * sizeof(wchar_t));

                RegGetValueW(HKEY_LOCAL_MACHINE,
                    L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                    L"ProcessorNameString",
                    RRF_RT_REG_SZ,
                    NULL,
                    outSnapshot.staticAnalytics.ProcessorNameString.data(),
                    &stringBufferSizeBytes);

                return true;
            }

            bool CPUReader::FetchCPUTicks(Model::Raw::CPU::stCPURawSnapshot& outSnapshot) {

                FILETIME idleTime, kernelTime, userTime;
                if (!GetSystemTimes(&idleTime, &kernelTime, &userTime)) return false;

                outSnapshot.dynamicAnalytics.rawTicks.rawIdleTicks = System::Reader::Util::ConvertFileTimeToUInt64(idleTime);
                outSnapshot.dynamicAnalytics.rawTicks.rawKernelTicks = System::Reader::Util::ConvertFileTimeToUInt64(kernelTime);
                outSnapshot.dynamicAnalytics.rawTicks.rawUserTicks = System::Reader::Util::ConvertFileTimeToUInt64(userTime);


                return true;
            }

            bool CPUReader::FetchDynamicAnalytics(Model::Raw::CPU::stCPURawSnapshot& outSnapshot) {

                PERFORMANCE_INFORMATION perfInfo;
                perfInfo.cb = sizeof(PERFORMANCE_INFORMATION);

                LARGE_INTEGER qpcTime;
                QueryPerformanceCounter(&qpcTime);
                outSnapshot.dynamicAnalytics.snapshotTimestamp.rawSystemTimeTimestamp = static_cast<uint64_t>(qpcTime.QuadPart);

                if (GetPerformanceInfo(&perfInfo, sizeof(perfInfo))) {
                    outSnapshot.dynamicAnalytics.totalActiveProcesses = static_cast<uint32_t>(perfInfo.ProcessCount);
                    outSnapshot.dynamicAnalytics.totalActiveThreads = static_cast<uint32_t>(perfInfo.ThreadCount);
                    outSnapshot.dynamicAnalytics.totalOpenedHandles = static_cast<uint32_t>(perfInfo.HandleCount);
                    return true;
                }
                return false;

            }

            bool CPUReader::FetchCPURawSnapshot(Model::Raw::CPU::stCPURawSnapshot& outSnapshot) {

                return (FetchCPUTicks(outSnapshot) && FetchDynamicAnalytics(outSnapshot));
            }

        }

    }
}
