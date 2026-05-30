#pragma once
#include <array>
#include <cstdint>

namespace System {
	namespace Model {
		namespace Hardware {
			namespace RAM {

				
				constexpr size_t MAX_SUPPORTED_DIMMS = 16;

				enum class enMemoryFormFactor : uint8_t {
					Unknown = 0,
					DIMM = 1,   
					SODIMM = 2  
				};

			
				struct stMemoryCounters
				{
					
					double totalPhysicalGb = 0.0;
					double usedPhysicalGb = 0.0;
					double availablePhysicalGb = 0.0;
					double memoryUtilizationPct = 0.0;

					
					double totalVirtualGb = 0.0;
					double usedVirtualGb = 0.0;
				};

		
				struct stRAMDTO
				{
					stMemoryCounters MemoryCounters;
					uint32_t activeDimmCount = 0;

					
					
					std::array<uint64_t, MAX_SUPPORTED_DIMMS> dimmCapacitiesBytes{};
					std::array<uint32_t, MAX_SUPPORTED_DIMMS> dimmClockSpeedsMhz{};
					std::array<enMemoryFormFactor, MAX_SUPPORTED_DIMMS> dimmFormFactors{};

					std::array<std::array<char, 32>, MAX_SUPPORTED_DIMMS> dimmManufacturers{};
				};

			}
		}
	}
}