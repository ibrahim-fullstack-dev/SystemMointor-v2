#pragma once
#include <array>
#include <cstdint>

namespace System {
	namespace Model {
		namespace Hardware {
			namespace Storage {

				
				constexpr size_t MAX_SUPPORTED_DISKS = 16;

				enum class enDiskType : uint8_t {
					Unknown = 0,
					HDD = 1,
					SSD = 2,
					NVMe = 3
				};


				struct stStorageCounters
				{
				
					double globalReadSpeedMbPs = 0.0;
					double globalWriteSpeedMbPs = 0.0;

					uint32_t totalActiveDisks = 0;
				};


				struct stStorageDTO
				{
					stStorageCounters StorageCounters;

					std::array<double, MAX_SUPPORTED_DISKS> diskTotalCapacitiesGb{};
					std::array<double, MAX_SUPPORTED_DISKS> diskUsedCapacitiesGb{};
					std::array<double, MAX_SUPPORTED_DISKS> diskUtilizationPct{};

					std::array<uint32_t, MAX_SUPPORTED_DISKS> diskIndexIds{}; 
					std::array<enDiskType, MAX_SUPPORTED_DISKS> diskTypes{};

					
					std::array<std::array<char, 32>, MAX_SUPPORTED_DISKS> diskNames{};        
					std::array<std::array<char, 16>, MAX_SUPPORTED_DISKS> fileSystems{};  
				};

			}
		}
	}
}