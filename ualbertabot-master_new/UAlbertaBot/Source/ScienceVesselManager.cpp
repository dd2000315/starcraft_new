#include "Common.h"
#include "ScienceVesselManager.h"
#include "UnitUtil.h"
#include "Micro.h"



using namespace UAlbertaBot;

ScienceVesselManager::ScienceVesselManager()
{
}

void ScienceVesselManager::executeMicro(const BWAPI::Unitset& targets)//可能需要获取其他Units的位置，比如rangedUnits（Squad.cpp）(错误)
{
    const BWAPI::Unitset& scienceVesselUnits = getUnits();

    BWAPI::Unitset detectReinforcementsTargets;
    if (detectReinforcementsTargets.empty())
    {
        for (auto& unit : BWAPI::Broodwar->self()->getUnits())
        {
            /*if (unit->getHitPoints() < unit->getInitialHitPoints() && !unit->getType().isWorker())
            {
                detectReinforcementsTargets.insert(unit);
            }*/
            if (unit->getType() == BWAPI::UnitTypes::Terran_Marine)
            {
                detectReinforcementsTargets.insert(unit);
            }
        }
    }
        

    
    
    BWAPI::Unitset availableVessel(scienceVesselUnits);

    for (auto& target : detectReinforcementsTargets)
    {
        for (auto& vessel : availableVessel)
        {
            double dist = vessel->getDistance(target);

            if (vessel)
            {
                Micro::SmartMove(vessel, target->getPosition());
                break;
            }
            else
            {
                break;
            }
        }
    }



    for (auto& vessel : availableVessel)
    {
        for (auto& unit : BWAPI::Broodwar->self()->getUnits())
        {
            /*if (unit->getHitPoints() < unit->getInitialHitPoints() && !unit->getType().isWorker())
            {
                detectReinforcementsTargets.insert(unit);
            }*/
            if (unit->getType() == BWAPI::UnitTypes::Terran_Medic)
            {
                Micro::SmartMove(vessel, unit->getPosition());
                break;
            }
        }
    }




    //for (auto& scienceVesselUnit : scienceVesselUnits)
    //{
        /*for (auto& unit : BWAPI::Broodwar->self()->getUnits())
        {

            if (unit->isUnderAttack() && !unit->isAttacking())
            {
                Micro::SmartMove(scienceVesselUnit, unit->getPosition());
                //movePriority = 2;
            }
            else if (unit->isUnderAttack())
            {
                Micro::SmartMove(scienceVesselUnit, unit->getPosition());
            }
            else if (unit->getType() == BWAPI::UnitTypes::Terran_Marine || unit->getType() == BWAPI::UnitTypes::Terran_Vulture || unit->getType() == BWAPI::UnitTypes::Terran_Goliath || unit->getType() == BWAPI::UnitTypes::Terran_Firebat)
            {
                Micro::SmartMove(scienceVesselUnit, unit->getPosition());
            }
            if(scienceVesselUnit ->isIdle())
            {
                Micro::SmartAttackMove(scienceVesselUnit, m_order.getPosition());
            }

        }*/
        /*if (scienceVesselUnit->isIdle())
        {
            Micro::SmartMove(scienceVesselUnit, m_order.getPosition());
        }*/
        //BWAPI::Unitset BWAPI::Broodwar->self()->getUnits();




        /*if (scienceVesselUnit->getHitPoints()<120)
        {
            BWAPI::Position fleeTo(BWAPI::Broodwar->self()->getStartLocation());
            Micro::SmartMove(scienceVesselUnit, fleeTo);
            
            const BWAPI::Unit repairWorker = worker.getClosestMineralWorkerTo(scienceVesselUnit);
            worker.setRepairWorker(repairWorker, scienceVesselUnit);

        }
        else
            continue;*/

    //}

   
    /*const BWAPI::Unitset& medics = getUnits();

    // create a set of all medic targets
    BWAPI::Unitset medicTargets;
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getHitPoints() < unit->getInitialHitPoints() && !unit->getType().isMechanical() && !unit->getType().isBuilding())
        {
            medicTargets.insert(unit);
        }
    }

    BWAPI::Unitset availableMedics(medics);

    // for each target, send the closest medic to heal it
    for (auto& target : medicTargets)
    {
        // only one medic can heal a target at a time
        if (target->isBeingHealed())
        {
            continue;
        }

        double closestMedicDist = std::numeric_limits<double>::infinity();
        BWAPI::Unit closestMedic = nullptr;

        for (auto& medic : availableMedics)
        {
            double dist = medic->getDistance(target);

            if (!closestMedic || (dist < closestMedicDist))
            {
                closestMedic = medic;
                closestMedicDist = dist;
            }
        }

        // if we found a medic, send it to heal the target
        if (closestMedic)
        {
            closestMedic->useTech(BWAPI::TechTypes::Healing, target);

            availableMedics.erase(closestMedic);
        }
        // otherwise we didn't find a medic which means they're all in use so break
        else
        {
            break;
        }
    }

    // the remaining medics should head to the squad order position
    for (auto& medic : availableMedics)
    {
        Micro::SmartAttackMove(medic, m_order.getPosition());
    }*/
}