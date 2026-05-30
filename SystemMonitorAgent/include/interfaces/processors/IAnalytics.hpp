#pragma once


namespace System {

	namespace Interface {

		template <typename TRawModel, typename TProcessedModel>
		class IAnalytics {
		public:

			virtual ~IAnalytics() = default;

			virtual bool GetAnalytics(TRawModel& raw, TProcessedModel& out) = 0;
		};
	}
}