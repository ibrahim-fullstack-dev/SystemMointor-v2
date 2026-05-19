#pragma once
#include "../../Enums/StatusLevel.h"
#include "../../interfaces/Global/IDescriptionProvider.h"

namespace System {

	namespace Interface {

		namespace RawData
		{
			class IStatusTypeProvider {

			public:
				// Virtual destructor for proper cleanup of derived classes.
				virtual ~IStatusTypeProvider() = default;

				virtual Enums::enStatusLevel GetStatus() const = 0;
			};

			class IStatusTypeAndMessageProvider : public IStatusTypeProvider, public Global::IDescriptionMessageProvider {

			public:
				// Virtual destructor for proper cleanup of derived classes.
				virtual ~IStatusTypeAndMessageProvider() = default;
			};

			class IStatusTypeAndMessageAndDescriptionProvider : public IStatusTypeProvider, public Global::IAdvancedDescriptionProvider {

			public:
				// Virtual destructor for proper cleanup of derived classes.
				virtual ~IStatusTypeAndMessageAndDescriptionProvider() = default;
			};

		}

	}
}
