#pragma once
#include "models/raw/hardware/CPURawModel.hpp"

namespace System {

    namespace Reader {

        namespace CPU {

            class CPUReader {

                
            public:

                bool FetchCPUTicks(Model::Raw::CPU::stCPURawSnapshot& outSnapshot);

                bool FetchStaticAnalytics(Model::Raw::CPU::stCPURawSnapshot& outSnapshot);

                bool FetchDynamicAnalytics(Model::Raw::CPU::stCPURawSnapshot& outSnapshot);

            };

            //class CoresReader {

            //    bool FetchCoreSnapshot(Model::Raw::CPU::stCoreRawSnapshot& outSnapshot);
            //};

            //class ProcessesReader {
            //    bool FetchProcessSnapshot(Model::Raw::CPU::stProcessRawSnapshot& outSnapshot);
            //};

            //class ThreadsReader {
            //    bool FetchThreadSnapshot(Model::Raw::CPU::stThreadRawSnapshot& outSnapshot);
            //};
        }
    }
}