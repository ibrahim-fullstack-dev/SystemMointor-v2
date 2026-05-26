#pragma once
#include <array>
#include <cstdint>

namespace System {
	namespace Model {
		namespace Hardware {
			namespace GPU {

				constexpr size_t MAX_SUPPORTED_GPUS = 8;

				enum class enGpuArchitecture : uint8_t {
					Unknown = 0,
					Integrated = 1, 
					Dedicated = 2   
				};

				
				struct stGpuCounters
				{
					
					double globalGpuPowerDrawWatts = 0.0;
					uint32_t totalActiveGpus = 0;
				};

				struct stGPUDTO
				{
					stGpuCounters GpuCounters;


					std::array<double, MAX_SUPPORTED_GPUS> gpuUtilizationPct{};  
					std::array<double, MAX_SUPPORTED_GPUS> vramTotalGb{};         
					std::array<double, MAX_SUPPORTED_GPUS> vramUsedGb{};        
					std::array<double, MAX_SUPPORTED_GPUS> vramUtilizationPct{};

					std::array<uint32_t, MAX_SUPPORTED_GPUS> gpuClockSpeedsMhz{}; 
					std::array<uint32_t, MAX_SUPPORTED_GPUS> gpuTemperatureC{};  

					std::array<enGpuArchitecture, MAX_SUPPORTED_GPUS> gpuArchitectures{}; 

					/
					std::array<std::array<char, 32>, MAX_SUPPORTED_GPUS> gpuNames{}; 
				};

			}
		}
	}
}