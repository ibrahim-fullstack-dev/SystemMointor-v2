#pragma once

namespace System {

    namespace Interface {

        namespace Enums {

            enum class ThermalState {
                Unknown = 0,
                Cool,
                Normal,
                Warm,
                Hot,
                Critical,
                Emergency
            };
        }
    }
}
