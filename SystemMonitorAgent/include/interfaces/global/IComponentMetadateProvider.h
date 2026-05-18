#pragma once

namespace System {

	namespace Interface {

		namespace Global
		{
			class ILabelCategoryProvider {
			public:
				// Virtual destructor for proper cleanup of derived classes.
				virtual ~ILabelCategoryProvider() = default;

				virtual const wchar_t* GetLabel() const = 0;
				virtual const wchar_t* GetCategory() const = 0;
			};

			
		}

	}
}
