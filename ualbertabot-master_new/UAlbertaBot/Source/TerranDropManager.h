#pragma once

#include <Common.h>
#include "MicroManager.h"
#include "RangedManager.h"

namespace UAlbertaBot
{
    class MicroManager;

    class TerranDropManager : public MicroManager
    {
        BWAPI::UnitInterface* m_dropShip = nullptr;
        //BWAPI::UnitInterface* m_dropShip2 = nullptr;
        BWAPI::Position					m_minCorner = { -1, -1 };
        BWAPI::Position					m_maxCorner = { -1, -1 };
        BWAPI::Position					m_to = { -1, -1 };
        BWAPI::Position					m_from = { -1, -1 };
        int                             m_currentRegionVertexIndex = -1;
        std::vector<BWAPI::Position>	m_waypoints;
        std::vector<BWAPI::Position>    m_mapEdgeVertices;

        RangedManager       m_rangedManager;//后加的

        void calculateMapEdgeVertices();
        void drawTransportInformation(int x, int y);
        void moveTransport();
        void moveTroops();
        void followPerimeter(int clockwise = 1);
        void followPerimeter(BWAPI::Position to, BWAPI::Position from);

        void loadUnits(BWAPI::Unitset units, int num);//自己写的

        int getClosestVertexIndex(BWAPI::UnitInterface* unit);
        int getClosestVertexIndex(BWAPI::Position p);
        BWAPI::Position getFleePosition(int clockwise = 1);
        std::pair<int, int> findSafePath(BWAPI::Position from, BWAPI::Position to);

        void assignTargetsOld(BWAPI::Unitset& rangedUnits);

        int getAttackPriority(BWAPI::Unit rangedUnit, BWAPI::Unit target);
        BWAPI::Unit closestrangedUnit(BWAPI::Unit target, std::set<BWAPI::Unit>& rangedUnitsToAssign);
        BWAPI::Unit getTarget(BWAPI::Unit rangedUnit, const BWAPI::Unitset& targets);
        std::pair<BWAPI::Unit, BWAPI::Unit> findClosestUnitPair(const BWAPI::Unitset& attackers, const BWAPI::Unitset& targets);

    public:

        TerranDropManager();

        void executeMicro(const BWAPI::Unitset& targets);
        void update();
        //void setTransportShip(BWAPI::UnitInterface* unit);
        void setFrom(BWAPI::Position from);
        void setTo(BWAPI::Position to);

        int dropUnitsNum = 0;
        int loadCount = 0;

        BWAPI::Unitset firebatTargets;

        bool dropShipreturning = false;
        bool dropOnce = false;
        BWAPI::Unitset availableDropUnits;
        BWAPI::Unitset afterDropUnits;
        BWAPI::Unitset availableDropShips;
        bool unitsLoading = false;
        bool unitsLoadFinished = false;
        bool shipToEnemyBase_ing = false;

        bool transportstop = false;
        bool availableDropUnitsFinished = false;
    };
}