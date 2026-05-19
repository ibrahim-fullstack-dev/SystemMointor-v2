#pragma once
#include <string>

namespace System {

	namespace Interface {

		namespace Global
		{
			class IDescriptionMessageProvider {

			public:
				virtual ~IDescriptionMessageProvider() = default;

				// Perfect: Returns a safe, managed wide string object
				virtual const std::wstring GetMessage() const = 0;

			};

			class IAdvancedDescriptionProvider : public IDescriptionMessageProvider {

			public:
				virtual ~IAdvancedDescriptionProvider() = default;

				virtual const std::wstring GetDescription() const = 0;
			};
		}
	}
}
