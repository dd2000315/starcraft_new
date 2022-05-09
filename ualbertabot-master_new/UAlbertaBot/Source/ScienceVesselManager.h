#pragma once

#include "MicroManager.h"
#include "WorkerManager.h"


namespace UAlbertaBot
{
    class ScienceVesselManager : public MicroManager
    {

        WorkerManager worker;
        
    public:

        ScienceVesselManager();
        void executeMicro(const BWAPI::Unitset& targets);
        //void detectMicro();
    };
}