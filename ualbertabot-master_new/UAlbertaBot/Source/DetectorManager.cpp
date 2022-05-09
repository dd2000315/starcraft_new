#include "Common.h"
#include "DetectorManager.h"
#include "Global.h"
#include "Micro.h"
#include "MapTools.h"

using namespace UAlbertaBot;

DetectorManager::DetectorManager()
{ 

}

void DetectorManager::executeMicro(const BWAPI::Unitset & targets)
{
    const BWAPI::Unitset & detectorUnits = getUnits();

    if (detectorUnits.empty())
    {
        return;
    }

    for (size_t i(0); i<targets.size(); ++i)
    {
        // do something here if there's targets
    }

    m_cloakedUnitMap.clear();
    BWAPI::Unitset cloakedUnits;

    // figure out targets
    for (auto & unit : BWAPI::Broodwar->enemy()->getUnits())
    {
        // conditions for targeting
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Lurker ||
            unit->getType() == BWAPI::UnitTypes::Protoss_Dark_Templar ||
            unit->getType() == BWAPI::UnitTypes::Terran_Wraith)
        {

            cloakedUnits.insert(unit);
            m_cloakedUnitMap[unit] = false;
        }
    }

    //bool detectorUnitInBattle = false;

    // for each detectorUnit
    for (auto & detectorUnit : detectorUnits)
    {
        // if we need to regroup, move the detectorUnit to that location
        //if (!detectorUnitInBattle && unitClosestToEnemy && unitClosestToEnemy->getPosition().isValid())
        if (unitClosestToEnemy && unitClosestToEnemy->getPosition().isValid())
        //if (!detectorUnitInBattle && !cloakedUnits.empty())
        {
            Micro::SmartMove(detectorUnit, unitClosestToEnemy->getPosition());
            //closestCloaked = closestCloakedUnit(cloakedUnits, detectorUnit);
            //Micro::SmartMove(detectorUnit, closestCloaked->getPosition());
            //detectorUnitInBattle = true;
            /*if (detectorUnit->getHitPoints() < 100 && detectorUnit->isUnderAttack())
            {

            }*/
        }
        /*else if (detectorUnit->getDistance(closestCloaked->getPosition())<288)
        {
            detectorUnit->useTech(7, closestCloaked);//Irradiate
        }*/
        //else if (detectorUnit->getDistance(unitClosestToEnemy->getPosition()) < 288)
        detectorAttackUnits = detectorUnit->getUnitsInRadius(300, BWAPI::Filter::IsEnemy);
        if (!detectorAttackUnits.empty())
        {
            for (auto& units : detectorAttackUnits)
            {
                if (units->getType() == BWAPI::UnitTypes::Zerg_Lurker && detectorUnit->getEnergy() > 75)
                {
                    detectorUnit->useTech(7, units);//Irradiate
                }
                else if (units->getType() == BWAPI::UnitTypes::Zerg_Hydralisk && detectorUnit->getEnergy() > 75)
                {
                    detectorUnit->useTech(7, units);
                }
                else if (units->getType() == BWAPI::UnitTypes::Zerg_Overlord && detectorUnit->getEnergy() > 75)
                {
                    detectorUnit->useTech(7, units);
                }
                else if (units->getType() == BWAPI::UnitTypes::Zerg_Drone && detectorUnit->getEnergy() > 75)
                {
                    detectorUnit->useTech(7, units);
                }
                
            }
            
        }
        detectorProtectUnits = detectorUnit->getUnitsInRadius(300, BWAPI::Filter::IsOwned);
        if (!detectorProtectUnits.empty())
        {
            for (auto& units : detectorProtectUnits)
            {
                if (units->getType() == BWAPI::UnitTypes::Terran_Science_Vessel && units->getHitPoints() == 80 && detectorUnit->getEnergy() > 100)
                {
                    detectorUnit->useTech(6, units);//Irradiate
                }
                /*if (units->getType() == BWAPI::UnitTypes::Zerg_Hydralisk && detectorUnit->getEnergy() > 75)
                {
                    detectorUnit->useTech(6, units);
                }*/

            }

        }
        /*if (cloakedUnits.empty())
        {
            for (auto& units : detectorAttackUnits)
            {
                
            }
        }*/
        
        // otherwise there is no battle or no closest to enemy so we don't want our detectorUnit to die
        
        // send him to scout around the map
        else
        {
            BWAPI::Position explorePosition = BWAPI::Position(Global::Map().getLeastRecentlySeenTile());
            Micro::SmartMove(detectorUnit, explorePosition);
        }
        detectorAttackUnits.clear();
    }
}


BWAPI::Unit DetectorManager::closestCloakedUnit(const BWAPI::Unitset & cloakedUnits, BWAPI::Unit detectorUnit)
{
    BWAPI::Unit closestCloaked = nullptr;
    double closestDist = 100000;

    for (auto & unit : cloakedUnits)
    {
        // if we haven't already assigned an detectorUnit to this cloaked unit
        if (!m_cloakedUnitMap[unit])
        {
            double dist = unit->getDistance(detectorUnit);

            if (!closestCloaked || (dist < closestDist))
            {
                closestCloaked = unit;
                closestDist = dist;
            }
        }
    }

    return closestCloaked;
}