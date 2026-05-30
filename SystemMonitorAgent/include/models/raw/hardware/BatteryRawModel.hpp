#pragma once
#include <array>
#include <cstdint>

namespace System {
	namespace Model {
		namespace Hardware {
			namespace Battery {

				constexpr size_t MAX_SUPPORTED_BATTERIES = 4;

				enum class enBatteryStatus : uint8_t {
					Unknown = 0,
					Discharging = 1, 
					Charging = 2,    
					FullyCharged = 3 
				};

				struct stPowerCounters
				{
					bool isAcOnline = false;         
					uint32_t totalConnectedBatteries = 0;
				};

				struct stBatteryDTO
				{
					stPowerCounters PowerCounters;


					std::array<double, MAX_SUPPORTED_BATTERIES> chargePercentages{};
					std::array<double, MAX_SUPPORTED_BATTERIES> voltageVolts{};      
					std::array<double, MAX_SUPPORTED_BATTERIES> temperatureCelsius{}; 
					std::array<uint32_t, MAX_SUPPORTED_BATTERIES> remainingTimeMins{}; 

					std::array<enBatteryStatus, MAX_SUPPORTED_BATTERIES> batteryStatuses{}; 

					
					std::array<std::array<char, 32>, MAX_SUPPORTED_BATTERIES> batteryNames{}; 
				};

			}
		}
	}
}