#pragma once
namespace System {

    namespace Interface {

        namespace Enums
        {
            enum class enBatteryState {

                Unknown = 0,
                Discharging,
                Charging,
                Full,
                NoBattery
            };
        }
    }
}