#pragma once
#include <array>
#include <cstdint>

namespace System {
	namespace Model {
		namespace Hardware {
			namespace Network {

				constexpr size_t MAX_SUPPORTED_ADAPTERS = 16;

				enum class enNetworkAdapterType : uint8_t {
					Unknown = 0,
					Ethernet = 1,
					WiFi = 2,
					Loopback = 3,
					Virtual = 4
				};


				struct stNetworkCounters
				{
					double globalDownloadSpeedMbPs = 0.0;
					double globalUploadSpeedMbPs = 0.0;

					uint32_t totalActiveAdapters = 0;
				};


				struct stNetworkDTO
				{
					stNetworkCounters NetworkCounters;


					std::array<double, MAX_SUPPORTED_ADAPTERS> adapterDownloadSpeedMbPs{}; 
					std::array<double, MAX_SUPPORTED_ADAPTERS> adapterUploadSpeedMbPs{};  
					std::array<uint64_t, MAX_SUPPORTED_ADAPTERS> totalBytesReceived{};     
					std::array<uint64_t, MAX_SUPPORTED_ADAPTERS> totalBytesSent{};         

					std::array<uint32_t, MAX_SUPPORTED_ADAPTERS> adapterIndexIds{};       
					std::array<enNetworkAdapterType, MAX_SUPPORTED_ADAPTERS> adapterTypes{}; 

					
					std::array<std::array<char, 64>, MAX_SUPPORTED_ADAPTERS> adapterNames{}; 
					std::array<std::array<char, 48>, MAX_SUPPORTED_ADAPTERS> macAddresses{}; 
				};

			}
		}
	}
}