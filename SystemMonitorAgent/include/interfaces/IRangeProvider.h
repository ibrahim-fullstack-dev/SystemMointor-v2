#pragma once // Ensure the header is included only once during compilation

namespace System {

	namespace Interface {

		namespace RawData
		{

			class IRangeProvider {

			public:
				virtual ~IRangeProvider() = default; // Virtual destructor for proper cleanup of derived classes.
				virtual double GetMin() const = 0;
				virtual double GetMax() const = 0;

			};
		}

		namespace ProcessedData
		{

			class IAdvancedRangeProvider : public RawData::IRangeProvider {

			public:
				virtual ~IAdvancedRangeProvider() = default; // Virtual destructor for proper cleanup of derived classes.

				virtual bool IsInRange(double value) const {
					return value >= GetMin() && value <= GetMax();
				}

			};
		}
	}
}


