#pragma once
#include <array>
#include <cstdint>
#include "../../../config/SystemLimits.hpp"
#include "../../../enums/EnumsProvider.hpp"

namespace System {

	namespace Model {

		namespace Hardware {

			namespace BLL {

				namespace CPU {

					struct stInterfaceCounters
					{
						double totalCpuUtilization = 0.0;
						double currentClockSpeedGhz = 0.0;
						double userTimePct = 0.0;
						double kernelTimePct = 0.0;
						double interruptTimePct = 0.0;
					};

					struct stTimelineAnalytics
					{
						uint32_t activeCoreCount = 0;
						uint32_t totalActiveProcesses = 0;
						uint32_t totalActiveThreads = 0;
					};

					struct stCPUDTO
					{
						stInterfaceCounters InterfaceCounters;
						stTimelineAnalytics TimelineAnalytics;
					};

					struct stCoreDTO
					{
						std::array<double, Config::Limits::MAX_SUPPORTED_CORES> componentLoads{};
						std::array<uint32_t, Config::Limits::MAX_SUPPORTED_CORES> logicalIds{};
						std::array<Enums::enCorePerformanceType, Config::Limits::MAX_SUPPORTED_CORES> coreTypes{};
					};

					struct stProcessDTO
					{
						std::array<double, Config::Limits::MAX_MONITORED_PROCESSES> cpuUsagePercents{};
						std::array<uint32_t, Config::Limits::MAX_MONITORED_PROCESSES> processIds{};
						std::array<std::array<char, 32>, Config::Limits::MAX_MONITORED_PROCESSES> processNames{};
					};

					struct stThreadDTO
					{
						uint32_t parentProcessId = 0;
						uint32_t activeThreadsCount = 0;

						std::array<double, Config::Limits::MAX_MONITORED_THREADS> threadCpuUsages{};
						std::array<uint32_t, Config::Limits::MAX_MONITORED_THREADS> threadIds{};
					};

				}
			}
		}
	}
}