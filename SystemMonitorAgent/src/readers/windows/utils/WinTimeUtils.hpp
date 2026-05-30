#pragma once
#include <Windows.h>
#include <cstdint>

namespace System {

    namespace Reader {

        namespace Util {

            static inline uint64_t ConvertFileTimeToUInt64(const FILETIME& ft) {
                return (static_cast<uint64_t>(ft.dwHighDateTime) << 32) | ft.dwLowDateTime;
            }
        }
    }
}
