#pragma once


namespace System {

	namespace Interface {

		template <typename TRawModel, typename TProcessedModel>
		class IUsage {

		public:
			virtual ~IUsage() = default;

			virtual bool GetUsage(const TRawModel& raw, TProcessedModel& out) = 0;
		};
	}
}