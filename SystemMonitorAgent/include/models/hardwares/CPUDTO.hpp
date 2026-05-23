#pragma once
#include <array>
#include <cstdint>

namespace System {

	namespace Model {

		namespace Hardware {

			//  To prevent random memory allocation, a fixed size was specified that is compatible with high - performance processing servers.
			constexpr size_t MAX_SUPPORTED_CORES = 128;

			enum class enCorePerformanceType : uint8_t {
				Unified = 0,
				Performance = 1,
				Efficiency = 2
			};

			//  Structure of Arrays (SoA) - Pure Flat Plain Data
			struct stCPUDTO
			{
				// Parallel arrays: Fetching a single cache line (64 bytes) pulls 8 cores together in the same clock pulse
				std::array<double, MAX_SUPPORTED_CORES> coreLoads{};

				std::array<uint32_t, MAX_SUPPORTED_CORES> logicalIds{};

				std::array<enCorePerformanceType, MAX_SUPPORTED_CORES> coreTypes{}; 

				// Padding =%0
				//  Total interface counters(Hero Widgets)
				double totalCpuUtilization = 0.0;
				double currentClockSpeedGhz = 0.0;
				double userTimePct = 0.0;
				double kernelTimePct = 0.0;
				double interruptTimePct = 0.0;

				//  Production line times (Timeline Analytics)
				uint32_t activeCoreCount = 0;
				uint32_t totalActiveProcesses = 0;
				uint32_t totalActiveThreads = 0;

				//  Instant query time wrapper
				unsigned long long queryTimestampUnixMilli = 0;
			};

		}
	}
}