#pragma once
#include "../../enums/ErrorTypes.h"
#include "../../interfaces/global/IDescriptionProvider.h"

namespace System {

	namespace Interface {

		namespace Global {

			class IErrorCodeProvider {
			public:
				// Virtual destructor for proper cleanup of derived classes.
				virtual ~IErrorCodeProvider() = default;
				virtual int GetErrorCode() const = 0;

			};

			class IErrorTypeProvider : public IErrorCodeProvider {
			public:
				
				virtual ~IErrorTypeProvider() = default;
				virtual System::Interface::Enums::enErrorType GetErrorType() const = 0;

			};

			class IErrorTypeAndMessageProvider : public IErrorTypeProvider, public IDescriptionMessageProvider {
			public:
				
				virtual ~IErrorTypeAndMessageProvider() = default;


			};

			class IErrorTypeAndMessageAndDescriptionProvider : public IErrorTypeProvider, public IAdvancedDescriptionProvider {
			public:
				
				virtual ~IErrorTypeAndMessageAndDescriptionProvider() = default;


			};
		}
	}
}




