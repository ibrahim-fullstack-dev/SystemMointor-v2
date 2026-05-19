#pragma once
#include "../../Enums/UnitType.h"

namespace System {

    namespace Interface {

        namespace ProcessedData {

            class IUnitProvider {
            public:
                virtual ~IUnitProvider() = default;

                virtual Enums::enUnitType GetUnitType() = 0;

            };

            class IUnitAdvanceProvider: public IUnitProvider {
            public:
                virtual ~IUnitAdvanceProvider() = default;

                virtual const char* GetUnitSymbol() = 0;
            };

        }
        
    }
}