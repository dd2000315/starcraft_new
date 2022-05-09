#include "ProductionManager.h"
#include "Global.h"
#include "BuildingData.h"
#include "BuildingManager.h"
#include "StrategyManager.h"
#include "BOSSManager.h"
#include "InformationManager.h"
#include "WorkerManager.h"

#include "MicroStrategyManager.h"
#include "UnitUtil.h"//后加的

using namespace UAlbertaBot;

ProductionManager::ProductionManager()
{
    setBuildOrder(Global::Strategy().getOpeningBookBuildOrder());
}

void ProductionManager::setBuildOrder(const BuildOrder & buildOrder)
{
    m_queue.clearAll();

    for (size_t i(0); i<buildOrder.size(); ++i)
    {
        m_queue.queueAsLowestPriority(buildOrder[i], true);
    }
}

void ProductionManager::performBuildOrderSearch()
{
    if (!Config::Modules::UsingBuildOrderSearch || !canPlanBuildOrderNow())//
    {
        return;
    }

    PROFILE_FUNCTION();

    BuildOrder & buildOrder = m_bossManager.getBuildOrder();

    if (buildOrder.size() > 0)
    {
        setBuildOrder(buildOrder);
        m_bossManager.reset();
    }
    else
    {
        if (!m_bossManager.isSearchInProgress())
        {
            m_bossManager.startNewSearch(Global::Strategy().getBuildOrderGoal());//从这里可以直接调出StrategyManager中的关于不同种族的不同初始
        }
    }
}

void ProductionManager::performBuildOrderSearch_custom()
{

    /*if (Config::Strategy::StrategyName == "Terran_3RaxPressure")
    {

    }*/

    int numWorkers = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_SCV);
    if (unitBuildQueueAppliedTimes == 0)
    {
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Medic), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Medic), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Medic), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Medic), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Factory), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Factory), true);

        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Barracks), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Barracks), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Barracks), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Barracks), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Barracks), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Barracks), true);

        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Supply_Depot), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Supply_Depot), true);

        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Dropship), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Firebat), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Firebat), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Firebat), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Firebat), true);

        


        unitBuildQueueAppliedTimes += 1;
    }
    else if (unitBuildQueueAppliedTimes == 1)
    {
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Medic), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Medic), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Medic), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Medic), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Supply_Depot), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Supply_Depot), true);

        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Barracks), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Barracks), true);

        unitBuildQueueAppliedTimes += 1;
    }
    else
    {
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Firebat), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Firebat), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Medic), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Medic), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Medic), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Medic), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);

        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Machine_Shop), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Machine_Shop), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Machine_Shop), true);

        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Supply_Depot), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Supply_Depot), true);

        unitBuildQueueAppliedTimes += 1;
    }
    
    /*if (SM.shouldExpandNow_custom() == true)
    {
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Command_Center), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);

    }*/

    /*if (numWorkers >= 18 && CommandCenterNum == 1)
    {
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Command_Center), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Refinery), true);
        CommandCenterNum += 1;
    }*/

    if (unitBuildQueueAppliedTimes == 4)
    {
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Command_Center), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Refinery), true);
        CommandCenterNum += 1;
    }

    if (numWorkers < 45)
    {
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
        //m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
    }
    int numScience_Vessel = UnitUtil::GetEnemyAllUnitCount(BWAPI::UnitTypes::Terran_Science_Vessel);
    if (numScience_Vessel <= 1)
    {
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
        m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
    }


}

void UAlbertaBot::ProductionManager::performBuildOrderSearch_custom2()
{
    int numWorkers = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_SCV);
    int numScienceVessel = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Science_Vessel);

    if (Config::Strategy::StrategyName == "Terran_3RaxPressure")
    {
        if (unitBuildQueueAppliedTimes == 0)
        {
            for (int i = 0; i < 12; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranMedicBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranScvBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranBarracksBuildPart(); }
            TerranSupplyDepotBuildPart();
            m_queue.queueAsLowestPriority(MetaType(BWAPI::TechTypes::Irradiate), true);
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UpgradeTypes::U_238_Shells), true);
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UpgradeTypes::Terran_Infantry_Weapons), true);
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UpgradeTypes::Terran_Infantry_Armor), true);
            for (int i = 0; i < 4; i++) { TerranFirebatBuildPart(); }
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
            unitBuildQueueAppliedTimes += 1;
        }
        if(unitBuildQueueAppliedTimes == 1)
        {
            for (int i = 0; i < 8; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 4; i++) { TerranFirebatBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranMedicBuildPart(); }
            for (int i = 0; i < 2; i++) { TerranBarracksBuildPart(); }
            unitBuildQueueAppliedTimes += 1;
        }
        if (unitBuildQueueAppliedTimes == 2)
        {
            for (int i = 0; i <20; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 4; i++) { TerranFirebatBuildPart(); }
            for (int i = 0; i < 2; i++) { TerranMedicBuildPart(); }
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UpgradeTypes::Terran_Infantry_Weapons), true);
            for (int i = 0; i < 12; i++) { TerranMarineBuildPart(); }
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UpgradeTypes::Terran_Infantry_Armor), true);
            unitBuildQueueAppliedTimes += 1;
        }
        if(unitBuildQueueAppliedTimes == 3)
        {
            for (int i = 0; i < 12; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranFirebatBuildPart(); }
            for (int i = 0; i < 2; i++) { TerranMedicBuildPart(); }
            unitBuildQueueAppliedTimes += 1;
        }
        if (unitBuildQueueAppliedTimes == 4)
        {
            for (int i = 0; i < 12; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranFirebatBuildPart(); }
            for (int i = 0; i < 2; i++) { TerranMedicBuildPart(); }
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UpgradeTypes::Terran_Infantry_Weapons), true);
            for (int i = 0; i < 12; i++) { TerranMarineBuildPart(); }
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UpgradeTypes::Terran_Infantry_Armor), true);
            unitBuildQueueAppliedTimes += 1;
        }
        else
        {
            for (int i = 0; i < 10; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranFirebatBuildPart(); }
            for (int i = 0; i < 1; i++) { TerranMedicBuildPart(); }
            unitBuildQueueAppliedTimes += 1;
        }
        if (int supply = BWAPI::Broodwar->self()->supplyTotal() < 200)
        {
            for (int i = 0; i < 2; i++) { TerranSupplyDepotBuildPart(); }
        }
        if (numWorkers < 40)
        {
            for (int i = 0; i < 2; i++) { TerranScvBuildPart(); }

        }
        if (numScienceVessel < 4)
        {
            TerranScienceVesselBuildPart();
        }
        if (UAlbertaBot::Global::Strategy().shouldExpandNow_custom())
        {
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Command_Center), true);
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Refinery), true);
            for (int i = 0; i < 5; i++) { TerranScvBuildPart(); }

        }

    }
    if (Config::Strategy::StrategyName == "Terran_DropTest")
    {
        if (unitBuildQueueAppliedTimes == 0)
        {
            for (int i = 0; i < 12; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 4; i++) { TerranMedicBuildPart(); }
            for (int i = 0; i < 4; i++) { TerranScvBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranBarracksBuildPart(); }
            TerranSupplyDepotBuildPart();
            TerranDropshipBuildPart();
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Command_Center), true);
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Refinery), true);
            m_queue.queueAsLowestPriority(MetaType(BWAPI::TechTypes::Irradiate), true);
            for (int i = 0; i < 4; i++) { TerranFirebatBuildPart(); }
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
            unitBuildQueueAppliedTimes += 1;
        }
        else if (unitBuildQueueAppliedTimes == 1)
        {
            for (int i = 0; i < 12; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 4; i++) { TerranMedicBuildPart(); }
            TerranSupplyDepotBuildPart();
            TerranSupplyDepotBuildPart();
            TerranSupplyDepotBuildPart();
            for (int i = 0; i < 3; i++) { TerranBarracksBuildPart(); }
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
            unitBuildQueueAppliedTimes += 1;
        }
        else
        {
            for (int i = 0; i < 12; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 4; i++) { TerranMedicBuildPart(); }
            TerranSupplyDepotBuildPart();
            TerranSupplyDepotBuildPart();
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
            unitBuildQueueAppliedTimes += 1;

        }


    }
    if (Config::Strategy::StrategyName == "Terran_WraithTest")
    {
        if (unitBuildQueueAppliedTimes == 0)
        {
            for (int i = 0; i < 20; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 4; i++) { TerranMedicBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranBarracksBuildPart(); }           
            TerranSupplyDepotBuildPart();
            TerranSupplyDepotBuildPart();
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Facility), true);
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Control_Tower), true);
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Control_Tower), true);
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Engineering_Bay), true);
            for (int i = 0; i < 8; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 2; i++) { TerranMedicBuildPart(); }
            for (int i = 0; i < 2; i++) { TerranScienceVesselBuildPart(); }
            unitBuildQueueAppliedTimes += 1;
        }
        else if (unitBuildQueueAppliedTimes == 1)
        {
            for (int i = 0; i <14; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranMedicBuildPart(); }
            TerranSupplyDepotBuildPart();
            TerranSupplyDepotBuildPart();
            unitBuildQueueAppliedTimes += 1;
        }
        else if (unitBuildQueueAppliedTimes == 2)
        {
            for (int i = 0; i < 18; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 2; i++) { TerranMedicBuildPart(); }
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UpgradeTypes::Terran_Infantry_Weapons), true);
        }
        else if (unitBuildQueueAppliedTimes == 3)
        {
            for (int i = 0; i < 12; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 2; i++) { TerranMedicBuildPart(); }
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UpgradeTypes::Terran_Infantry_Armor), true);

        }
        else
        {
            for (int i = 0; i < 12; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 2; i++) { TerranMedicBuildPart(); }
            unitBuildQueueAppliedTimes += 1;

        }
        if (numWorkers < 40)
        {
            for (int i = 0; i < 2; i++) { TerranScvBuildPart(); }

        }
        if (numScienceVessel < 4)
        {
            TerranScienceVesselBuildPart();
        }
        if (int supply = BWAPI::Broodwar->self()->supplyTotal() < 200)
        {
            for (int i = 0; i < 2; i++) { TerranSupplyDepotBuildPart(); }
        }
        if (UAlbertaBot::Global::Strategy().shouldExpandNow_custom())
        {
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Command_Center), true);
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Refinery), true);
            for (int i = 0; i < 5; i++) { TerranScvBuildPart(); }
            
        }
        

    }
    if (Config::Strategy::StrategyName == "Terran_5RaxPressure")
    {
        if (unitBuildQueueAppliedTimes == 0)
        {
            for (int i = 0; i < 20; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranMedicBuildPart(); }
            for (int i = 0; i < 2; i++) { TerranBarracksBuildPart(); }
            TerranSupplyDepotBuildPart();
            TerranSupplyDepotBuildPart();
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Machine_Shop), true);
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Machine_Shop), true);
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Machine_Shop), true);
            for (int i = 0; i < 12; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 2; i++) { TerranMedicBuildPart(); }
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UpgradeTypes::Terran_Vehicle_Weapons), true);
            unitBuildQueueAppliedTimes += 1;
        }
        else if (unitBuildQueueAppliedTimes == 1)
        {
            for (int i = 0; i < 18; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranMedicBuildPart(); }
            TerranSupplyDepotBuildPart();
            TerranSupplyDepotBuildPart();
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Factory), true);
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Factory), true);
            for (int i = 0; i < 3; i++) { TerranSiegeTankBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranVultureBuildPart(); }
            unitBuildQueueAppliedTimes += 1;
        }
        else if (unitBuildQueueAppliedTimes == 2)
        {
            for (int i = 0; i < 12; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 2; i++) { TerranMedicBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranSiegeTankBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranVultureBuildPart(); }
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UpgradeTypes::Terran_Infantry_Weapons), true);
        }
        else if (unitBuildQueueAppliedTimes == 3)
        {
            for (int i = 0; i < 12; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 2; i++) { TerranMedicBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranSiegeTankBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranVultureBuildPart(); }
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UpgradeTypes::Terran_Vehicle_Weapons), true);
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UpgradeTypes::Terran_Infantry_Armor), true);

        }
        else
        {
            for (int i = 0; i < 12; i++) { TerranMarineBuildPart(); }
            for (int i = 0; i < 2; i++) { TerranMedicBuildPart(); }
            for (int i = 0; i < 3; i++) { TerranSiegeTankBuildPart(); }
            for (int i = 0; i < 6; i++) { TerranVultureBuildPart(); }
            unitBuildQueueAppliedTimes += 1;

        }
        if (numWorkers < 40)
        {
            for (int i = 0; i < 2; i++) { TerranScvBuildPart(); }

        }
        if (numScienceVessel < 4)
        {
            TerranScienceVesselBuildPart();
        }
        if (int supply = BWAPI::Broodwar->self()->supplyTotal() < 200)
        {
            for (int i = 0; i < 2; i++) { TerranSupplyDepotBuildPart(); }
        }
        if (UAlbertaBot::Global::Strategy().shouldExpandNow_custom())
        {
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Command_Center), true);
            m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Refinery), true);
            for (int i = 0; i < 5; i++) { TerranScvBuildPart(); }

        }
    }
}

void UAlbertaBot::ProductionManager::TerranMarineBuildPart()
{
    m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Marine), true);
}

void UAlbertaBot::ProductionManager::TerranMedicBuildPart()
{
    m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Medic), true);
}

void UAlbertaBot::ProductionManager::TerranScvBuildPart()
{
    m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_SCV), true);
}

void UAlbertaBot::ProductionManager::TerranBarracksBuildPart()
{
    m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Barracks), true);
}

void UAlbertaBot::ProductionManager::TerranSupplyDepotBuildPart()
{
    m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Supply_Depot), true);
}

void UAlbertaBot::ProductionManager::TerranDropshipBuildPart()
{
    m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Dropship), true);
}

void UAlbertaBot::ProductionManager::TerranFirebatBuildPart()
{
    m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Firebat), true);
}

void UAlbertaBot::ProductionManager::TerranGoliathBuildPart()
{
    m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Goliath), true);
}

void UAlbertaBot::ProductionManager::TerranCommandCenterBuildPart()
{
    m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Command_Center), true);
}

void UAlbertaBot::ProductionManager::TerranRefineryBuildPart()
{
    m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Refinery), true);
}

void UAlbertaBot::ProductionManager::TerranScienceVesselBuildPart()
{
    m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
}

void UAlbertaBot::ProductionManager::TerranSiegeTankBuildPart()
{
    m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode), true);
}

void UAlbertaBot::ProductionManager::TerranVultureBuildPart()
{
    m_queue.queueAsLowestPriority(MetaType(BWAPI::UnitTypes::Terran_Vulture), true);
}







void ProductionManager::update()//单位建设的主要函数
{
    PROFILE_FUNCTION();

    m_buildingManager.update();

    // 30 ms per search update
    //m_bossManager.update(Config::Macro::BOSSTimePerFrame);

    // check the _queue for stuff we can build
    manageBuildOrderQueue();

    int numMarines = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Marine);
    int numMedics = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Medic);
    int numVultures = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Vulture);
    int numGoliath = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Goliath);
    int numFactory = UnitUtil::GetEnemyAllUnitCount(BWAPI::UnitTypes::Terran_Factory);
    int numArmory = UnitUtil::GetEnemyAllUnitCount(BWAPI::UnitTypes::Terran_Armory);
    int numAcademy = UnitUtil::GetEnemyAllUnitCount(BWAPI::UnitTypes::Terran_Academy);
    int numScience_Vessel = UnitUtil::GetEnemyAllUnitCount(BWAPI::UnitTypes::Terran_Science_Vessel);

    //int numstrategyAppliyedTimes = UAlbertaBot::StrategyManager::m_strategyAppliyedTimes;

    BWAPI::Broodwar->drawTextScreen(430, 90, "Terran_Marine num %d", numMarines);
    BWAPI::Broodwar->drawTextScreen(430, 100, "Terran_Medic num %d", numMedics);
    BWAPI::Broodwar->drawTextScreen(430, 110, "Terran_Vulture num %d", numVultures);
    BWAPI::Broodwar->drawTextScreen(430, 120, "Terran_Goliath num %d", numGoliath);
    BWAPI::Broodwar->drawTextScreen(430, 130, "Terran_Factory num %d", numFactory);
    //BWAPI::Broodwar->drawTextScreen(430, 140, "BuildOrderGoal Applied Times %d", UAlbertaBot::StrategyManager::m_strategyAppliyedTimes);


    /*if (Global::MStrategy().detect_Zerg_Lurker() == true)//自己写的
    {
        if (m_enemyLurkerdetected == false)
        {
            m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
            m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
            m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
            m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Control_Tower), true);
            m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Control_Tower), true);
            m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Facility), true);
            m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Starport), true);
            m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Starport), true);
            
            m_enemyLurkerdetected = true;
        }
        if (numScience_Vessel >= 1)
        {
            m_scienceVesselhasbeendeployed = true;
        }
        if (numScience_Vessel == 0 && m_scienceVesselhasbeendeployed == true)
        {
            m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
            m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
        }
    }*/

        //else if(numScience_Vessel)

        /*else if (m_enemyLurkerdetected == true)
        {
            for (const auto& unit : BWAPI::Broodwar->self()->getUnits())
            {
                if (unit->getType() == BWAPI::UnitTypes::Terran_Science_Facility)
                {
                    flag_build_Terran_Science_Facility = false;
                }
                else if (unit->getType() == BWAPI::UnitTypes::Terran_Starport)
                {
                    flag_build_Terran_Starport = false;
                }
                else if (unit->getType() == BWAPI::UnitTypes::Terran_Control_Tower)
                {
                    flag_build_Terran_Control_Tower = false;
                }
                else if (unit->getType() == BWAPI::UnitTypes::Terran_Science_Vessel)
                {
                    flag_build_Terran_Science_Vessel = false;
                }
            }
            if (flag_build_Terran_Science_Vessel == true)
            {
                m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
            }
            if (flag_build_Terran_Science_Facility == true)
            {
                m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Facility), true);
            }
            if (flag_build_Terran_Control_Tower == true)
            {
                m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Control_Tower), true);
            }
            if (flag_build_Terran_Starport == true)
            {
                m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Starport), true);
            }





        }


    }*/

    //if nothing is currently building, get a new goal from the strategy manager
    if ((m_queue.size() < 6) && (BWAPI::Broodwar->getFrameCount() > 10))
    {
        if (Config::Debug::DrawBuildOrderSearchInfo)
        {
            BWAPI::Broodwar->drawTextScreen(150, 10, "Nothing left to build, new search!");
        }

        //performBuildOrderSearch_custom();
        performBuildOrderSearch_custom2();

    }


    /*if (Global::MStrategy().detect_Zerg_Lurker() == true)//自己写的
    {
        m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Facility), true);
        m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Starport), true);
        m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Control_Tower), true);
        m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
        m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);

    }*/

    // detect if there's a build order deadlock once per second
        if ((BWAPI::Broodwar->getFrameCount() % 24 == 0) && detectBuildOrderDeadlock())
        {
            if (Config::Debug::DrawBuildOrderSearchInfo)
            {
                BWAPI::Broodwar->printf("Supply deadlock detected, building supply!");
            }
            m_queue.queueAsHighestPriority(MetaType(BWAPI::Broodwar->self()->getRace().getSupplyProvider()), true);
        }

        // if they have cloaked units get a new goal asap
        if (!m_enemyCloakedDetected && Global::Info().enemyHasCloakedUnits())//对付隐形单位的措施
        {
            if (BWAPI::Broodwar->self()->getRace() == BWAPI::Races::Protoss)
            {
                if (BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Photon_Cannon) < 2)
                {
                    m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Protoss_Photon_Cannon), true);
                    m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Protoss_Photon_Cannon), true);
                }

                if (BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Forge) == 0)
                {
                    m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Protoss_Forge), true);
                }
            }
            else if (BWAPI::Broodwar->self()->getRace() == BWAPI::Races::Terran)
            {
                if (BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Terran_Missile_Turret) < 2)
                {
                    m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Missile_Turret), true);
                    m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Missile_Turret), true);
                }

                if (BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Terran_Engineering_Bay) == 0)
                {
                    m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Engineering_Bay), true);
                }

                if (BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Terran_Factory) == 0)
                {
                    m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Factory), true);
                }

                if (BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Terran_Starport) == 0)
                {
                    m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Starport), true);
                }

                if (BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Terran_Science_Vessel) == 0)
                {
                    m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
                    m_queue.queueAsHighestPriority(MetaType(BWAPI::UnitTypes::Terran_Science_Vessel), true);
                }


            }

            if (Config::Debug::DrawBuildOrderSearchInfo)
            {
                BWAPI::Broodwar->printf("Enemy Cloaked Unit Detected!");
            }

            m_enemyCloakedDetected = true;
        }

        /*if (m_queue.isEmpty())
        {
            performBuildOrderSearch();
        }*/
        

        
        m_bossManager.drawSearchInformation(490, 100);
        m_bossManager.drawStateInformation(250, 0);
}

// on unit destroy
void ProductionManager::onUnitDestroy(BWAPI::Unit unit)
{
    // we don't care if it's not our unit
    if (!unit || unit->getPlayer() != BWAPI::Broodwar->self())
    {
        return;
    }

    if (Config::Modules::UsingBuildOrderSearch)
    {
        // if it's a worker or a building, we need to re-search for the current goal
        if ((unit->getType().isWorker() && !Global::Workers().isWorkerScout(unit)) || unit->getType().isBuilding())
        {
            if (unit->getType() != BWAPI::UnitTypes::Zerg_Drone)
            {
                //performBuildOrderSearch_custom();
                performBuildOrderSearch_custom2();
            }
        }
    }
}

void ProductionManager::manageBuildOrderQueue()//对于建造顺序的管理。
{
    PROFILE_FUNCTION();

    // if there is nothing in the _queue, oh well
    if (m_queue.isEmpty())
    {
        return;
    }

    // the current item to be used
    BuildOrderItem & currentItem = m_queue.getHighestPriorityItem();

    // while there is still something left in the _queue
    while (!m_queue.isEmpty())
    {
        // this is the unit which can produce the currentItem
        BWAPI::Unit producer = getProducer(currentItem.metaType);

        // check to see if we can make it right now
        bool canMake = canMakeNow(producer, currentItem.metaType);

        // if we try to build too many refineries manually remove it
        //可能后期会删掉。
        if (currentItem.metaType.isRefinery() && (BWAPI::Broodwar->self()->allUnitCount(BWAPI::Broodwar->self()->getRace().getRefinery() >= 3)))
        {
            m_queue.removeCurrentHighestPriorityItem();
            break;
        }

        // if the next item in the list is a building and we can't yet make it
        if (currentItem.metaType.isBuilding() && !(producer && canMake) && currentItem.metaType.whatBuilds().isWorker())
        {
            // construct a temporary building object
            Building b(currentItem.metaType.getUnitType(), BWAPI::Broodwar->self()->getStartLocation());
            b.isGasSteal = currentItem.isGasSteal;

            // set the producer as the closest worker, but do not set its job yet
            producer = Global::Workers().getBuilder(b, false);

            // predict the worker movement to that building location
            predictWorkerMovement(b);
        }

        // if we can make the current item
        if (producer && canMake)
        {
            // create it
            create(producer, currentItem);
            m_assignedWorkerForThisBuilding = false;
            m_haveLocationForThisBuilding = false;

            // and remove it from the _queue
            m_queue.removeCurrentHighestPriorityItem();

            // don't actually loop around in here
            break;
        }
        // otherwise, if we can skip the current item
        else if (m_queue.canSkipItem())
        {
            // skip it
            m_queue.skipItem();

            // and get the next one
            currentItem = m_queue.getNextHighestPriorityItem();
        }
        else
        {
            // so break out
            break;
        }
    }
}

BWAPI::Unit ProductionManager::getProducer(MetaType t, BWAPI::Position closestTo)//从这里开始都是一些生产上具体细节的操作。(新的认识：这里是主要对于要生产的单位进行种类判断，尤其是其是否为挂件)
{
    PROFILE_FUNCTION();

    // get the type of unit that builds this
    BWAPI::UnitType producerType = t.whatBuilds();

    // make a set of all candidate producers
    BWAPI::Unitset candidateProducers;
    for (auto & unit : BWAPI::Broodwar->self()->getUnits())
    {
        UAB_ASSERT(unit != nullptr, "Unit was null");

        // reasons a unit can not train the desired type
        if (unit->getType() != producerType) { continue; }
        if (!unit->isCompleted()) { continue; }
        if (unit->isTraining()) { continue; }
        if (unit->isLifted()) { continue; }
        if (!unit->isPowered()) { continue; }

        // if the type is an addon, some special cases
        if (t.getUnitType().isAddon())
        {
            // if the unit already has an addon, it can't make one
            if (unit->getAddon() != nullptr)
            {
                continue;
            }

            // if we just told this unit to build an addon, then it will not be building another one
            // this deals with the frame-delay of telling a unit to build an addon and it actually starting to build
            if (unit->getLastCommand().getType() == BWAPI::UnitCommandTypes::Build_Addon
                && (BWAPI::Broodwar->getFrameCount() - unit->getLastCommandFrame() < 10))
            {
                continue;
            }

            bool isBlocked = false;

            // if the unit doesn't have space to build an addon, it can't make one
            BWAPI::TilePosition addonPosition(unit->getTilePosition().x + unit->getType().tileWidth(), unit->getTilePosition().y + unit->getType().tileHeight() - t.getUnitType().tileHeight());
            BWAPI::Broodwar->drawBoxMap(addonPosition.x*32, addonPosition.y*32, addonPosition.x*32 + 64, addonPosition.y*32 + 64, BWAPI::Colors::Red);

            for (int i=0; i<unit->getType().tileWidth() + t.getUnitType().tileWidth(); ++i)
            {
                for (int j=0; j<unit->getType().tileHeight(); ++j)
                {
                    BWAPI::TilePosition tilePos(unit->getTilePosition().x + i, unit->getTilePosition().y + j);

                    // if the map won't let you build here, we can't build it
                    if (!BWAPI::Broodwar->isBuildable(tilePos))
                    {
                        isBlocked = true;
                        BWAPI::Broodwar->drawBoxMap(tilePos.x*32, tilePos.y*32, tilePos.x*32 + 32, tilePos.y*32 + 32, BWAPI::Colors::Red);
                    }

                    // if there are any units on the addon tile, we can't build it
                    BWAPI::Unitset uot = BWAPI::Broodwar->getUnitsOnTile(tilePos.x, tilePos.y);
                    if (uot.size() > 0 && !(uot.size() == 1 && *(uot.begin()) == unit))
                    {
                        isBlocked = true;;
                        BWAPI::Broodwar->drawBoxMap(tilePos.x*32, tilePos.y*32, tilePos.x*32 + 32, tilePos.y*32 + 32, BWAPI::Colors::Red);
                    }
                }
            }

            if (isBlocked)
            {
                continue;
            }
        }

        // if the type requires an addon and the producer doesn't have one
        typedef std::pair<BWAPI::UnitType, int> ReqPair;
        for (const ReqPair & pair : t.getUnitType().requiredUnits())
        {
            BWAPI::UnitType requiredType = pair.first;
            if (requiredType.isAddon())
            {
                if (!unit->getAddon() || (unit->getAddon()->getType() != requiredType))
                {
                    continue;
                }
            }
        }

        // if we haven't cut it, add it to the set of candidates
        candidateProducers.insert(unit);
    }

    return getClosestUnitToPosition(candidateProducers, closestTo);
}

BWAPI::Unit ProductionManager::getClosestUnitToPosition(const BWAPI::Unitset & units, BWAPI::Position closestTo)
{
    if (units.size() == 0)
    {
        return nullptr;
    }

    // if we don't care where the unit is return the first one we have
    if (closestTo == BWAPI::Positions::None)
    {
        return *(units.begin());
    }

    BWAPI::Unit closestUnit = nullptr;
    double minDist(1000000);

    for (auto & unit : units)
    {
        UAB_ASSERT(unit != nullptr, "Unit was null");

        double distance = unit->getDistance(closestTo);
        if (!closestUnit || distance < minDist)
        {
            closestUnit = unit;
            minDist = distance;
        }
    }

    return closestUnit;
}

// this function will check to see if all preconditions are met and then create a unit
void ProductionManager::create(BWAPI::Unit producer, BuildOrderItem & item)
{
    if (!producer)
    {
        return;
    }

    PROFILE_FUNCTION();

    MetaType t = item.metaType;

    // if we're dealing with a building
    if (t.isUnit() && t.getUnitType().isBuilding()
        && t.getUnitType() != BWAPI::UnitTypes::Zerg_Lair
        && t.getUnitType() != BWAPI::UnitTypes::Zerg_Hive
        && t.getUnitType() != BWAPI::UnitTypes::Zerg_Greater_Spire
        && !t.getUnitType().isAddon())
    {
        // send the building task to the building manager
        m_buildingManager.addBuildingTask(t.getUnitType(), BWAPI::Broodwar->self()->getStartLocation(), item.isGasSteal);
    }
    else if (t.getUnitType().isAddon())
    {
        //BWAPI::TilePosition addonPosition(producer->getTilePosition().x + producer->getType().tileWidth(), producer->getTilePosition().y + producer->getType().tileHeight() - t.unitType.tileHeight());
        producer->buildAddon(t.getUnitType());
    }
    // if we're dealing with a non-building unit
    else if (t.isUnit())
    {
        // if the race is zerg, morph the unit
        if (t.getUnitType().getRace() == BWAPI::Races::Zerg)
        {
            producer->morph(t.getUnitType());
            // if not, train the unit
        }
        else
        {
            producer->train(t.getUnitType());
        }
    }
    // if we're dealing with a tech research
    else if (t.isTech())
    {
        producer->research(t.getTechType());
    }
    else if (t.isUpgrade())
    {
        //Logger::Instance().log("Produce Upgrade: " + t.getName() + "\n");
        producer->upgrade(t.getUpgradeType());
    }
    else
    {

    }
}

bool ProductionManager::canMakeNow(BWAPI::Unit producer, MetaType t)
{
    //UAB_ASSERT(producer != nullptr, "Producer was null");

    bool canMake = meetsReservedResources(t);
    if (canMake)
    {
        if (t.isUnit())
        {
            canMake = BWAPI::Broodwar->canMake(t.getUnitType(), producer);
        }
        else if (t.isTech())
        {
            canMake = BWAPI::Broodwar->canResearch(t.getTechType(), producer);
        }
        else if (t.isUpgrade())
        {
            canMake = BWAPI::Broodwar->canUpgrade(t.getUpgradeType(), producer);
        }
        else
        {
            UAB_ASSERT(false, "Unknown type");
        }
    }

    return canMake;
}

bool ProductionManager::detectBuildOrderDeadlock()
{
    // if the _queue is empty there is no deadlock
    if (m_queue.size() == 0 || BWAPI::Broodwar->self()->supplyTotal() >= 390)
    {
        return false;
    }

    // are any supply providers being built currently
    bool supplyInProgress =	m_buildingManager.isBeingBuilt(BWAPI::Broodwar->self()->getRace().getSupplyProvider());

    for (auto & unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Egg)
        {
            if (unit->getBuildType() == BWAPI::UnitTypes::Zerg_Overlord)
            {
                supplyInProgress = true;
                break;
            }
        }
    }

    // does the current item being built require more supply

    int supplyCost			= m_queue.getHighestPriorityItem().metaType.supplyRequired();
    int supplyAvailable		= std::max(0, BWAPI::Broodwar->self()->supplyTotal() - BWAPI::Broodwar->self()->supplyUsed());

    // if we don't have enough supply and none is being built, there's a deadlock
    if ((supplyAvailable < supplyCost) && !supplyInProgress)
    {
        // if we're zerg, check to see if a building is planned to be built
        if (BWAPI::Broodwar->self()->getRace() == BWAPI::Races::Zerg && m_buildingManager.buildingsQueued().size() > 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    return false;
}

// When the next item in the _queue is a building, this checks to see if we should move to it
// This function is here as it needs to access prodction manager's reserved resources info
void ProductionManager::predictWorkerMovement(const Building & b)
{
    if (b.isGasSteal)
    {
        return;
    }

    // get a possible building location for the building
    if (!m_haveLocationForThisBuilding)
    {
        m_predictedTilePosition = m_buildingManager.getBuildingLocation(b);
    }

    if (m_predictedTilePosition != BWAPI::TilePositions::None)
    {
        m_haveLocationForThisBuilding = true;
    }
    else
    {
        return;
    }

    // draw a box where the building will be placed
    int x1 = m_predictedTilePosition.x * 32;
    int x2 = x1 + (b.type.tileWidth()) * 32;
    int y1 = m_predictedTilePosition.y * 32;
    int y2 = y1 + (b.type.tileHeight()) * 32;
    if (Config::Debug::DrawWorkerInfo)
    {
        BWAPI::Broodwar->drawBoxMap(x1, y1, x2, y2, BWAPI::Colors::Blue, false);
    }

    // where we want the worker to walk to
    BWAPI::Position walkToPosition		= BWAPI::Position(x1 + (b.type.tileWidth()/2)*32, y1 + (b.type.tileHeight()/2)*32);

    // compute how many resources we need to construct this building
    int mineralsRequired				= std::max(0, b.type.mineralPrice() - getFreeMinerals());
    int gasRequired						= std::max(0, b.type.gasPrice() - getFreeGas());

    // get a candidate worker to move to this location
    BWAPI::Unit moveWorker			= Global::Workers().getMoveWorker(walkToPosition);

    // Conditions under which to move the worker: 
    //		- there's a valid worker to move
    //		- we haven't yet assigned a worker to move to this location
    //		- the build position is valid
    //		- we will have the required resources by the time the worker gets there
    if (moveWorker && m_haveLocationForThisBuilding && !m_assignedWorkerForThisBuilding && (m_predictedTilePosition != BWAPI::TilePositions::None) &&
        Global::Workers().willHaveResources(mineralsRequired, gasRequired, moveWorker->getDistance(walkToPosition)))
    {
        // we have assigned a worker
        m_assignedWorkerForThisBuilding = true;

        // tell the worker manager to move this worker
        Global::Workers().setMoveWorker(mineralsRequired, gasRequired, walkToPosition);
    }
}

void ProductionManager::performCommand(BWAPI::UnitCommandType t)
{
    // if it is a cancel construction, it is probably the extractor trick
    if (t == BWAPI::UnitCommandTypes::Cancel_Construction)
    {
        BWAPI::Unit extractor = nullptr;
        for (auto & unit : BWAPI::Broodwar->self()->getUnits())
        {
            if (unit->getType() == BWAPI::UnitTypes::Zerg_Extractor)
            {
                extractor = unit;
            }
        }

        if (extractor)
        {
            extractor->cancelConstruction();
        }
    }
}

int ProductionManager::getFreeMinerals()
{
    return BWAPI::Broodwar->self()->minerals() - m_buildingManager.getReservedMinerals();
}

int ProductionManager::getFreeGas()
{
    return BWAPI::Broodwar->self()->gas() - m_buildingManager.getReservedGas();
}

// return whether or not we meet resources, including building reserves
bool ProductionManager::meetsReservedResources(MetaType type)
{
    // return whether or not we meet the resources
    return (type.mineralPrice() <= getFreeMinerals()) && (type.gasPrice() <= getFreeGas());
}


// selects a unit of a given type
BWAPI::Unit ProductionManager::selectUnitOfType(BWAPI::UnitType type, BWAPI::Position closestTo)
{
    // if we have none of the unit type, return nullptr right away
    if (BWAPI::Broodwar->self()->completedUnitCount(type) == 0)
    {
        return nullptr;
    }

    BWAPI::Unit unit = nullptr;

    // if we are concerned about the position of the unit, that takes priority
    if (closestTo != BWAPI::Positions::None)
    {
        double minDist(1000000);

        for (auto & u : BWAPI::Broodwar->self()->getUnits())
        {
            if (u->getType() == type)
            {
                double distance = u->getDistance(closestTo);
                if (!unit || distance < minDist) {
                    unit = u;
                    minDist = distance;
                }
            }
        }

        // if it is a building and we are worried about selecting the unit with the least
        // amount of training time remaining
    }
    else if (type.isBuilding())
    {
        for (auto & u : BWAPI::Broodwar->self()->getUnits())
        {
            UAB_ASSERT(u != nullptr, "Unit was null");

            if (u->getType() == type && u->isCompleted() && !u->isTraining() && !u->isLifted() &&u->isPowered()) {

                return u;
            }
        }
        // otherwise just return the first unit we come across
    }
    else
    {
        for (auto & u : BWAPI::Broodwar->self()->getUnits())
        {
            UAB_ASSERT(u != nullptr, "Unit was null");

            if (u->getType() == type && u->isCompleted() && u->getHitPoints() > 0 && !u->isLifted() &&u->isPowered())
            {
                return u;
            }
        }
    }

    // return what we've found so far
    return nullptr;
}

void ProductionManager::drawProductionInformation(int x, int y)
{
    if (!Config::Debug::DrawProductionInfo)
    {
        return;
    }

    // fill prod with each unit which is under construction
    std::vector<BWAPI::Unit> prod;
    for (auto & unit : BWAPI::Broodwar->self()->getUnits())
    {
        UAB_ASSERT(unit != nullptr, "Unit was null");

        if (unit->isBeingConstructed())
        {
            prod.push_back(unit);
        }
    }

    // sort it based on the time it was started
    std::sort(prod.begin(), prod.end(), CompareWhenStarted());

    BWAPI::Broodwar->drawTextScreen(x-30, y+20, "\x04 TIME");
    BWAPI::Broodwar->drawTextScreen(x, y+20, "\x04 UNIT NAME");

    size_t reps = prod.size() < 10 ? prod.size() : 10;

    y += 30;
    int yy = y;

    // for each unit in the _queue
    for (auto & unit : prod)
    {
        std::string prefix = "\x07";

        yy += 10;

        BWAPI::UnitType t = unit->getType();
        if (t == BWAPI::UnitTypes::Zerg_Egg)
        {
            t = unit->getBuildType();
        }

        BWAPI::Broodwar->drawTextScreen(x, yy, " %s%s", prefix.c_str(), t.getName().c_str());
        BWAPI::Broodwar->drawTextScreen(x - 35, yy, "%s%6d", prefix.c_str(), unit->getRemainingBuildTime());
    }

    m_queue.drawQueueInformation(x, yy+10);
}

void ProductionManager::queueGasSteal()
{
    m_queue.queueAsHighestPriority(MetaType(BWAPI::Broodwar->self()->getRace().getRefinery()), true, true);
}

// this will return true if any unit is on the first frame if it's training time remaining
// this can cause issues for the build order search system so don't plan a search on these frames
bool ProductionManager::canPlanBuildOrderNow() const
{
    for (const auto & unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getRemainingTrainTime() == 0)
        {
            continue;
        }

        BWAPI::UnitType trainType = unit->getLastCommand().getUnitType();

        if (unit->getRemainingTrainTime() == trainType.buildTime())
        {
            return false;
        }
    }

    return true;
}

std::vector<BWAPI::UnitType> ProductionManager::buildingsQueued()
{
    return m_buildingManager.buildingsQueued();
}