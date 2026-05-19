#pragma once // Ensure the header is included only once during compilation

namespace System {

	namespace Interface {

		namespace RawData
		{
			class ICapacityProvider {
			public:
				virtual ~ICapacityProvider() = default; // Virtual destructor for proper cleanup of derived classes.
				virtual double GetCapacity() const = 0;
				
			};

			class ICapacityAdvancedProvider: public ICapacityProvider {
			public:
				virtual ~ICapacityAdvancedProvider() = default;
				
				virtual double GetUsedCapacity() const = 0;
			};
		}

	}
}


