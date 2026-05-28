#pragma once
#include "models/dal/hardware/CPURawModel.hpp"

namespace System {

    namespace Reader {

        namespace CPU {

            class CPUReader {

                
            public:

                 CpuReader();
                ~CpuReader() = default;

                bool FetchCPUTicks(Model::Raw::CPU::& outSnapshot);

                bool FetchStaticAnalytics(Model::Raw::CPU::& outSnapshot);

                bool FetchDynamicAnalytics(Model::Raw::CPU::& outSnapshot);

                bool FetchCPURawSnapshot(Model::Raw::CPU::& outSnapshot);
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