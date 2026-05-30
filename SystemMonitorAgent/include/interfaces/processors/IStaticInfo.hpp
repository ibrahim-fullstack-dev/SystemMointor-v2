#pragma once


namespace System {

	namespace Interface {

		template <typename TRawModel, typename TProcessedModel>
		class IStaticInfo {
		public:

			virtual ~IStaticInfo() = default;

			virtual bool GetInfo(const TRawModel& raw, TProcessedModel& out) = 0;
		};
	}
}