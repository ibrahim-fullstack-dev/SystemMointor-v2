#pragma once


namespace System {

	namespace Interface {

		template <typename TRawModel, typename TProcessedModel>
		class IGetUsage {

		public:
			virtual ~IGetUsage() = default;

			virtual bool GetUsage(const TRawModel& raw, TProcessedModel& out) = 0;
		};
	}
}