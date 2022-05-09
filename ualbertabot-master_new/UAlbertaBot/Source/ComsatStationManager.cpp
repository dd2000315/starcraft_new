#include "Common.h"
#include "ComsatStationManager.h"
#include "BaseLocationManager.h"
#include "Global.h"
#include "Micro.h"
#include "MapTools.h"

using namespace UAlbertaBot;

ComsatStationManager::ComsatStationManager()
{

}

void ComsatStationManager::executeMicro(const BWAPI::Unitset& targets)
{
    const BWAPI::Unit& ComsatStationUnit = getUnit();

    if (ComsatStationUnit == nullptr)
    {
        return;
    }

    scannerBase(ComsatStationUnit);
}





    
void ComsatStationManager::scannerBase(BWAPI::Unit unit)
{
    auto enemyBaseLocation = Global::Bases().getPlayerStartingBaseLocation(BWAPI::Broodwar->enemy());
    int zergLurkerCount = 0;


    /*for (auto& units : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getEnergy() > 50 && unit->exists())
        {
            unit->useTech(4, enemyBaseLocation->getPosition());
        }
    }*/

    for (auto& units : BWAPI::Broodwar->self()->getUnits())
    {
        if (units->getType() == BWAPI::UnitTypes::Zerg_Lurker)
        {
            zergLurkerCount += 1;
            if (unit->getEnergy() > 50 && unit->exists())
            {
                unit->useTech(4, units->getPosition());
            }
        }
    }

    if (zergLurkerCount == 0)
    {
        unit->useTech(4, enemyBaseLocation->getPosition());
    }
    
    
}