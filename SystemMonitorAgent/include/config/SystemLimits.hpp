#pragma once
#include <cstddef>

namespace System {
    namespace Config {
        namespace Limits {

			// The single source of truth for all the limits used in CPU monitoring, which are designed to be compatible with high-performance processing servers. These limits are set to prevent random memory allocation and ensure efficient performance.
            constexpr size_t MAX_SUPPORTED_CORES = 128;
            constexpr size_t MAX_MONITORED_PROCESSES = 128;
            constexpr size_t MAX_MONITORED_THREADS = 128;

        }
    }
}