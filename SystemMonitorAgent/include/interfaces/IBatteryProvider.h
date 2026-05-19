#pragma once
#include "../../Enums/BatteryState.h"
#include "../Global/IDescriptionProvider.h"

namespace System {

	namespace Interface {

		namespace ProcessedData {

			class IBatteryStateProvider {

			public:

				virtual ~IBatteryStateProvider() = default;
				virtual Enums::enBatteryState GetState() const = 0;

			};

			class IBatteryStateAndMessageProvider : public IBatteryStateProvider, public Global::IDescriptionMessageProvider {
			public:
				virtual ~IBatteryStateAndMessageProvider() = default;
			};

			class IBatteryStateAndMessageAndDescriptionProvider : public IBatteryStateProvider, public Global::IAdvancedDescriptionProvider {
				public:
				virtual ~IBatteryStateAndMessageAndDescriptionProvider() = default;
			};

		}
	}
}
