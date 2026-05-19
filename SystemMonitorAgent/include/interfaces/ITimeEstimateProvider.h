#pragma once

namespace System {

	namespace Interface {

		namespace RawData
		{
			class ITimestampProvider {
			public:
				// Virtual destructor for proper cleanup of derived classes.
				virtual ~ITimestampProvider() = default;
				virtual long long GetTimestamp() const = 0; // Return timestamp in milliseconds since epoch
			};
		}
	}
}
