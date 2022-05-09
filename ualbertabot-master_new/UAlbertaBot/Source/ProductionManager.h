#pragma once

#include <Common.h>
#include "BuildOrderQueue.h"
#include "BOSSManager.h"
#include "BuildingManager.h"
//#include "StrategyManager.h"

namespace UAlbertaBot
{
typedef unsigned char Action;

class Building;
class BuildOrder;

class ProductionManager
{
    friend class Global;

    BuildingManager     m_buildingManager;
    BOSSManager         m_bossManager;
    BuildOrderQueue     m_queue;

    //StrategyManager SM;

    
    BWAPI::TilePosition m_predictedTilePosition;
    bool                m_enemyCloakedDetected          = false;
    bool                m_assignedWorkerForThisBuilding = false;
    bool                m_haveLocationForThisBuilding   = false;

    bool                m_enemyLurkerdetected = false;//自己写的
    bool                m_scienceVesselhasbeendeployed = false;
    
    bool                flag_build_Terran_Science_Facility = true;//同上
    bool                flag_build_Terran_Starport = true;//同上
    bool                flag_build_Terran_Control_Tower = true;//同上
    bool                flag_build_Terran_Science_Vessel = true;//同上

    int                 unitBuildQueueAppliedTimes = 0;
    int                 CommandCenterNum = 1;









    BWAPI::Unit         getClosestUnitToPosition(const BWAPI::Unitset & units, BWAPI::Position closestTo);
    BWAPI::Unit         selectUnitOfType(BWAPI::UnitType type, BWAPI::Position closestTo = BWAPI::Position(0, 0));

    void setBuildOrder(const BuildOrder & buildOrder);
    void create(BWAPI::Unit producer, BuildOrderItem & item);
    void manageBuildOrderQueue();
    void performCommand(BWAPI::UnitCommandType t);
    void predictWorkerMovement(const Building & b);

    int  getFreeMinerals();
    int  getFreeGas();
    bool detectBuildOrderDeadlock();
    bool canPlanBuildOrderNow() const;
    bool canMakeNow(BWAPI::Unit producer, MetaType t);
    bool meetsReservedResources(MetaType type);
    
    ProductionManager();

public:

    void update();
    void onUnitDestroy(BWAPI::Unit unit);
    void performBuildOrderSearch();
    void performBuildOrderSearch_custom();//自己写的
    void performBuildOrderSearch_custom2();
    void TerranMarineBuildPart();
    void TerranMedicBuildPart();
    void TerranScvBuildPart();
    void TerranBarracksBuildPart();
    void TerranSupplyDepotBuildPart();
    void TerranDropshipBuildPart();
    void TerranFirebatBuildPart();
    void TerranGoliathBuildPart();
    void TerranCommandCenterBuildPart();
    void TerranRefineryBuildPart();
    void TerranScienceVesselBuildPart();
    void TerranSiegeTankBuildPart();
    void TerranVultureBuildPart();



    void drawProductionInformation(int x, int y);
    void queueGasSteal();
    std::vector<BWAPI::UnitType> buildingsQueued();

    BWAPI::Unit getProducer(MetaType t, BWAPI::Position closestTo = BWAPI::Positions::None);

    //StrategyManager SM;
};


class CompareWhenStarted
{

public:

    CompareWhenStarted() {}

    // the sorting operator
    bool operator() (BWAPI::Unit u1, BWAPI::Unit u2)
    {
        int startedU1 = BWAPI::Broodwar->getFrameCount() - (u1->getType().buildTime() - u1->getRemainingBuildTime());
        int startedU2 = BWAPI::Broodwar->getFrameCount() - (u2->getType().buildTime() - u2->getRemainingBuildTime());
        return startedU1 > startedU2;
    }
};
}