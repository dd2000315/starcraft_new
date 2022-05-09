#pragma once

#include "MicroManager.h"
#include "BaseLocation.h"

namespace UAlbertaBot
{
    class WraithManager : public MicroManager
    {
        //std::map<BWAPI::Unit, bool>	m_cloakedUnitMap;
        //BWAPI::Unit unitClosestToEnemy = nullptr;

        //BWAPI::Unit closestCloaked;
        



    public:

        WraithManager();


        void executeMicro(const BWAPI::Unitset& targets);

        void attackMainBase(BWAPI::Unitset unit);
        void attackSubBase(BWAPI::Unitset unit);
        void supplementaryForce(BWAPI::Unitset unit);

        //WAPI::Unitset ComsatStationUnits;
        bool initWraithSquad = false;

        BWAPI::Unitset wraithMainUnits;
        //BWAPI::Unitset wraithSubUnits;

        bool WraithInFighting = false;

        int getAttackPriority(BWAPI::Unit rangedUnit, BWAPI::Unit target);
        BWAPI::Unit closestrangedUnit(BWAPI::Unit target, std::set<BWAPI::Unit>& rangedUnitsToAssign);
        BWAPI::Unit getTarget(BWAPI::Unit rangedUnit, const BWAPI::Unitset& targets);
        std::pair<BWAPI::Unit, BWAPI::Unit> findClosestUnitPair(const BWAPI::Unitset& attackers, const BWAPI::Unitset& targets);

    };
}