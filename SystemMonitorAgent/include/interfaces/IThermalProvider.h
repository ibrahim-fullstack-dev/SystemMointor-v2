#pragma once // Ensure the header is included only once during compilation
#include "../../Enums/ThermalState.h"
#include "../Global/IDescriptionProvider.h"

namespace System {

	namespace Interface {

		namespace RawData
		{

			class IThermalProvider {
			public:
				virtual ~IThermalProvider() = default; // Virtual destructor for proper cleanup of derived classes .
				virtual double GetTemperature() const = 0;
			};
		}

		namespace ProcessedData
		{

			class IThermalStateProvider {
			public:
				virtual ~IThermalStateProvider() = default;
				virtual Enums::ThermalState GetThermalState() const = 0;
			};
			
			class IThermalStateAndMessageProvider: public IThermalStateProvider, public Global::IDescriptionMessageProvider {
			public:
				virtual ~IThermalStateAndMessageProvider() = default;
				
			};

			class IThermalStateAndMessageAndDescriptionProvider : public IThermalStateProvider, public Global::IAdvancedDescriptionProvider {
			public:
				virtual ~IThermalStateAndMessageAndDescriptionProvider() = default;
			};
		}
	}
}


