#pragma once

#include "MicroManager.h"

namespace UAlbertaBot
{
    class ComsatStationManager : public MicroManager
    {
        //std::map<BWAPI::Unit, bool>	m_cloakedUnitMap;
        BWAPI::Unit unitClosestToEnemy = nullptr;

        BWAPI::Unit closestCloaked;



    public:

        ComsatStationManager();

        
        void executeMicro(const BWAPI::Unitset& targets);

        void scannerBase(BWAPI::Unit unit);

        //BWAPI::Unit ComsatStationUnits;
    };
}