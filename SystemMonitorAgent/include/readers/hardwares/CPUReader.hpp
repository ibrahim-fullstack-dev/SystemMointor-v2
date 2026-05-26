#pragma once

// Prevent Pre-Compiled Models. 
namespace System {

    namespace Model {

        namespace Hardware {

            namespace DAL {

                namespace CPU {
                    struct stCPURawSnapshot;
                    struct stCoreRawSnapshot;
                    struct stProcessRawSnapshot;
                    struct stThreadRawSnapshot;
                }
            }
        }
    }
}

namespace System {

    namespace Reader {

        namespace Hardware {

            namespace CPUReader {

                bool FetchCPUSnapshot(Model::Hardware::DAL::CPU::stCPURawSnapshot& outSnapshot);
            }

            namespace CoresReader {

                bool FetchCoreSnapshot(Model::Hardware::DAL::CPU::stCoreRawSnapshot& outSnapshot);
            }

            namespace ProcessesReader {
                bool FetchProcessSnapshot(Model::Hardware::DAL::CPU::stProcessRawSnapshot& outSnapshot);
            }

            namespace ThreadsReader {
                bool FetchThreadSnapshot(Model::Hardware::DAL::CPU::stThreadRawSnapshot& outSnapshot);
            }

        }

    }
}