#include "Common.h"
#include "MicroStrategyManager.h"
#include "UnitUtil.h"
#include "BaseLocationManager.h"
#include "Global.h"
#include "InformationManager.h"
#include "WorkerManager.h"
#include "Logger.h"


using namespace UAlbertaBot;

MicroStrategyManager::MicroStrategyManager()
    : m_selfRace(BWAPI::Broodwar->self()->getRace())
    , m_enemyRace(BWAPI::Broodwar->enemy()->getRace())
    , m_emptyBuildOrder(BWAPI::Broodwar->self()->getRace())
{

}

void MicroStrategyManager::update()
{
    detect_Zerg_Lurker();

}

bool MicroStrategyManager::detect_Zerg_Lurker()
{
    for (const auto& unit : BWAPI::Broodwar->enemy()->getUnits())
    {
        if (Zerg_lurker_has_been_found == true)
        {
            return true;
        }

        if (unit->getType() == BWAPI::UnitTypes::Zerg_Lurker)
        {
            BWAPI::Broodwar->drawTextScreen(500, 70, "Zerg_Lurker has been found.");
            Zerg_lurker_has_been_found = true;
            return true;
        }

        /*else
        {
            BWAPI::Broodwar->drawTextScreen(500, 70, "Zerg_Lurker has not been found.");
            return false;
        }*/
    }
}



/*const MetaPairVector MicroStrategyManager::getForLurkerBuildOrderGoal() const
{
    std::vector<MetaPair> goal;

    int numScience_Vessel = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Science_Vessel);

    BWAPI::Broodwar->drawTextScreen(500, 70, "Zerg_Lurker has been found.");
    goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Science_Facility, 1));
    goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Starport, 1));
    goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Control_Tower, 1));
    if (numScience_Vessel < 2)
    {
        goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Science_Vessel, numScience_Vessel + 1));
    }
    

    return goal;
}

void MicroStrategyManager::getForLurkerBuildOrderGoal(std::vector<MetaPair> goal)
{
    
    int numScience_Vessel = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Science_Vessel);

    BWAPI::Broodwar->drawTextScreen(450, 80, "Zerg_Lurker has been found, Start construction plan.");
    goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Science_Facility, 1));
    goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Starport, 1));
    goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Control_Tower, 1));
    if (numScience_Vessel < 2)
    {
        goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Science_Vessel, numScience_Vessel + 1));
    }

}*/

