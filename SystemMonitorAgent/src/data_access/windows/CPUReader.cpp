#pragma once
#include <windows.h>
#include <cstdint>
#include <array>
#include "models/hardwares/CPUDTO.hpp"

namespace System {
    namespace DAL {
        namespace Hardware {

            namespace CPU {

                void FetchCoreMetrics(
                    FILETIME& inOutPrevIdle,
                    FILETIME& inOutPrevKernel,
                    FILETIME& inOutPrevUser,
                    Model::Hardware::CPU::stCPUDTO& outCpuDTO);
            }

            namespace Cores {

                void FetchPerCoreMetrics(
                    std::array<FILETIME, Model::Hardware::CPU::MAX_SUPPORTED_CORES>& inOutPrevCoresIdle,
                    std::array<FILETIME, Model::Hardware::CPU::MAX_SUPPORTED_CORES>& inOutPrevCoresKernel,
                    std::array<FILETIME, Model::Hardware::CPU::MAX_SUPPORTED_CORES>& inOutPrevCoresUser,
                    Model::Hardware::CPU::stCoreDTO& outCoresDTO);

            }
            
            namespace Processes {
               
                void FetchAll(Model::Hardware::CPU::stProcessDTO& outProcessDTO);
            }

            namespace Threads {

                
                void FetchForProcess(uint32_t targetProcessId, Model::Hardware::CPU::stThreadDTO& outThreadDTO);
            }

        }
    }
}