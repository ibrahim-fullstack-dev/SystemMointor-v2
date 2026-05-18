#pragma once

namespace System
{
    namespace Interface {

        namespace Enums {

            enum class enErrorType {
                Success = 0,
                AccessDenied,
                NotSupported,
                InvalidHandle,
                NoData,
                DeviceDisconnected,
                UnknownError
            };
        }
    }
}