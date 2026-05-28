#pragma once
#include "models/dal/hardware/CPURawModel.hpp"

namespace System {

    namespace Reader {

        namespace CPU {

            class CPUReader {

                
            public:

                 CpuReader();
                ~CpuReader() = default;

                bool FetchCPUTicks(Model::Hardware::DAL::CPU::stCPURawSnapshot& outSnapshot);

                bool FetchStaticAnalytics(Model::Hardware::DAL::CPU::stCPURawSnapshot& outSnapshot);

                bool FetchDynamicAnalytics(Model::Hardware::DAL::CPU::stCPURawSnapshot& outSnapshot);

                bool FetchCPURawSnapshot(Model::Hardware::DAL::CPU::stCPURawSnapshot& outSnapshot);
            };

            class CoresReader {

                bool FetchCoreSnapshot(Model::Hardware::DAL::CPU::stCoreRawSnapshot& outSnapshot);
            };

            class ProcessesReader {
                bool FetchProcessSnapshot(Model::Hardware::DAL::CPU::stProcessRawSnapshot& outSnapshot);
            };

            class ThreadsReader {
                bool FetchThreadSnapshot(Model::Hardware::DAL::CPU::stThreadRawSnapshot& outSnapshot);
            };
        }
    }
}