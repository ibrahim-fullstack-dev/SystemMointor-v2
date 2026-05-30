#pragma once

namespace System {

	namespace Interface {

		template <typename TRawModel, typename TProcessedModel>
		class IGetUsage {

			virtual ~IGetUsage() = default;

			virtual bool GetUsage(TRawModel& raw, TProcessedModel& out) = 0;
		};
	}
}