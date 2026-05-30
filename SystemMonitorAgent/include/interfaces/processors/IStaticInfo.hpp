#pragma once


namespace System {

	namespace Interface {

		template <typename TRawModel, typename TProcessedModel>
		class IGetInfo {
		public:

			virtual ~IGetInfo() = default;

			virtual bool GetInfo(TRawModel& raw, TProcessedModel& out) = 0;
		};
	}
}