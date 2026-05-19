#pragma once
#include <string>

namespace System {

	namespace Interface {

		namespace Global
		{
			class ILabelCategoryProvider {
			public:
				// Virtual destructor for proper cleanup of derived classes.
				virtual ~ILabelCategoryProvider() = default;

				virtual const std::wstring GetLabel() const = 0;
				virtual const std::wstring GetCategory() const = 0;
			};

			
		}

	}
}
