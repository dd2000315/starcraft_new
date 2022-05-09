#include "Common.h"
#include "WraithManager.h"
#include "BaseLocationManager.h"
#include "Global.h"
#include "Micro.h"
#include "MapTools.h"
#include "UnitUtil.h"

using namespace UAlbertaBot;

WraithManager::WraithManager()
{

}

void WraithManager::executeMicro(const BWAPI::Unitset& targets)
{
    const BWAPI::Unitset& wraithUnits = getUnits();

    


    if (wraithUnits.empty())
    {
        return;
    }

    supplementaryForce(wraithUnits);

    for (auto& units : wraithMainUnits)
    {
        if (!units->exists())
        {
            wraithMainUnits.erase(units);
        }
    }

    

    if (wraithMainUnits.size() >= 5)
    {
        attackMainBase(wraithMainUnits);
    }
    

}

void UAlbertaBot::WraithManager::attackMainBase(BWAPI::Unitset unit)
{
    BWAPI::Broodwar->drawTextScreen(430, 100, "attackMainBase conduct");
    auto enemyBaseLocation = Global::Bases().getPlayerStartingBaseLocation(BWAPI::Broodwar->enemy());
    BWAPI::Unit enemy;
   

    BWAPI::Unitset wraithTargets;

    if (enemyBaseLocation->getGroundDistance(wraithMainUnits.getPosition()) < 100)
    {
        wraithTargets = wraithMainUnits.getUnitsInRadius(224, BWAPI::Filter::IsEnemy);

    }


    for (auto& rangedUnit : wraithMainUnits)
    {
        
        if (m_order.getType() == SquadOrderTypes::Attack || m_order.getType() == SquadOrderTypes::Defend)
        {
            // if there are targets
            if (!wraithTargets.empty())
            {
                // find the best target for this zealot
                BWAPI::Unit target = getTarget(rangedUnit, wraithTargets);

                if (target && Config::Debug::DrawUnitTargetInfo)
                {
                    BWAPI::Broodwar->drawLineMap(rangedUnit->getPosition(), rangedUnit->getTargetPosition(), BWAPI::Colors::Purple);
                }


                // attack it
                if (Config::Micro::KiteWithRangedUnits)
                {
                    if (rangedUnit->getType() == BWAPI::UnitTypes::Zerg_Mutalisk || rangedUnit->getType() == BWAPI::UnitTypes::Terran_Vulture || rangedUnit->getType() == BWAPI::UnitTypes::Terran_Wraith)
                    {
                        Micro::MutaDanceTarget(rangedUnit, target);
                    }
                    else
                    {
                        Micro::SmartKiteTarget(rangedUnit, target);
                    }
                }
                else
                {
                    Micro::SmartAttackUnit(rangedUnit, target);
                }
            }
            // if there are no targets
            else
            {
                // if we're not near the order position
                if (rangedUnit->getDistance(enemyBaseLocation->getPosition()) > 100)
                {
                    // move to it
                    Micro::SmartAttackMove(rangedUnit, enemyBaseLocation->getPosition());
                }
            }
        }
    }
}

/*void UAlbertaBot::WraithManager::attackSubBase(BWAPI::Unitset unit)
{
    BWAPI::Broodwar->drawTextScreen(430, 110, "attackMainBase conduct");
    if (WraithInFighting == true)
    {
        return;
    }
    for (auto& base : Global::Bases().getBaseLocations())
    {
        if (base->isStartLocation())
        {
            continue;
        }
        else
        {
            wraithSubUnits.move(base->getPosition());
            BWAPI::Unitset wraithTargets;

            if (base->getGroundDistance(wraithSubUnits.getPosition()) < 100)
            {
                wraithTargets = wraithSubUnits.getUnitsInRadius(224, BWAPI::Filter::IsEnemy);

            }

            if (wraithTargets.empty())
            {
                continue;
            }
            else
            {
                WraithInFighting = true;
                for (auto& rangedUnit : wraithSubUnits)
                {
                    // train sub units such as scarabs or interceptors
                    //trainSubUnits(rangedUnit);

                    // if the order is to attack or defend
                    if (m_order.getType() == SquadOrderTypes::Attack || m_order.getType() == SquadOrderTypes::Defend)
                    {
                        // if there are targets
                        if (!wraithTargets.empty())
                        {
                            // find the best target for this zealot
                            BWAPI::Unit target = getTarget(rangedUnit, wraithTargets);

                            if (target && Config::Debug::DrawUnitTargetInfo)
                            {
                                BWAPI::Broodwar->drawLineMap(rangedUnit->getPosition(), rangedUnit->getTargetPosition(), BWAPI::Colors::Purple);
                            }


                            // attack it
                            if (Config::Micro::KiteWithRangedUnits)
                            {
                                if (rangedUnit->getType() == BWAPI::UnitTypes::Zerg_Mutalisk || rangedUnit->getType() == BWAPI::UnitTypes::Terran_Vulture || rangedUnit->getType() == BWAPI::UnitTypes::Terran_Wraith)
                                {
                                    Micro::MutaDanceTarget(rangedUnit, target);
                                }
                                else
                                {
                                    Micro::SmartKiteTarget(rangedUnit, target);
                                }
                            }
                            else
                            {
                                Micro::SmartAttackUnit(rangedUnit, target);
                            }
                        }
                        // if there are no targets
                        else
                        {
                            // if we're not near the order position
                            //if (rangedUnit->getDistance(base->getPosition()) > 100)
                            //{
                                // move to it
                                //Micro::SmartAttackMove(rangedUnit, base->getPosition());
                            //}
                            WraithInFighting = false;
                            continue;
                        }
                    }
                }
            }



        }

    }
}*/

void UAlbertaBot::WraithManager::supplementaryForce(BWAPI::Unitset unit)
{
    for (auto& newunit : unit)
    {
        if (wraithMainUnits.find(newunit) != wraithMainUnits.end())
        {
            continue;
        }
        if (wraithMainUnits.find(newunit) == wraithMainUnits.end())
        {
            //if (wraithMainUnits.size() == 6)
            //{
                wraithMainUnits.insert(newunit);
            //}
            /*else
            {
                wraithSubUnits.insert(newunit);
            }*/
        }

    }
}

std::pair<BWAPI::Unit, BWAPI::Unit> WraithManager::findClosestUnitPair(const BWAPI::Unitset& attackers, const BWAPI::Unitset& targets)
{
    std::pair<BWAPI::Unit, BWAPI::Unit> closestPair(nullptr, nullptr);
    double closestDistance = std::numeric_limits<double>::max();

    for (auto& attacker : attackers)
    {
        BWAPI::Unit target = getTarget(attacker, targets);
        double dist = attacker->getDistance(attacker);

        if (!closestPair.first || (dist < closestDistance))
        {
            closestPair.first = attacker;
            closestPair.second = target;
            closestDistance = dist;
        }
    }

    return closestPair;
}

// get a target for the zealot to attack
BWAPI::Unit WraithManager::getTarget(BWAPI::Unit rangedUnit, const BWAPI::Unitset& targets)
{
    int bestPriorityDistance = 1000000;
    int bestPriority = 0;

    double bestLTD = 0;

    int highPriority = 0;
    double closestDist = std::numeric_limits<double>::infinity();
    BWAPI::Unit closestTarget = nullptr;

    for (const auto& target : targets)
    {
        double distance = rangedUnit->getDistance(target);
        double LTD = UnitUtil::CalculateLTD(target, rangedUnit);
        int priority = getAttackPriority(rangedUnit, target);
        bool targetIsThreat = LTD > 0;

        if (!closestTarget || (priority > highPriority) || (priority == highPriority && distance < closestDist))
        {
            closestDist = distance;
            highPriority = priority;
            closestTarget = target;
        }
    }

    return closestTarget;
}

// get the attack priority of a type in relation to a zergling
int WraithManager::getAttackPriority(BWAPI::Unit rangedUnit, BWAPI::Unit target)
{
    BWAPI::UnitType rangedType = rangedUnit->getType();
    BWAPI::UnitType targetType = target->getType();


    if (rangedUnit->getType() == BWAPI::UnitTypes::Zerg_Scourge)
    {
        if (target->getType() == BWAPI::UnitTypes::Protoss_Carrier)
        {

            return 100;
        }

        if (target->getType() == BWAPI::UnitTypes::Protoss_Corsair)
        {
            return 90;
        }
    }

    if (target->getType() == BWAPI::UnitTypes::Zerg_Drone)
    {
        return 101;
    }

    if (target->getType() == BWAPI::UnitTypes::Zerg_Hydralisk)
    {
        return 102;
    }

    if (target->getType() == BWAPI::UnitTypes::Zerg_Overlord)
    {
        return 103;
    }

    bool isThreat = rangedType.isFlyer() ? targetType.airWeapon() != BWAPI::WeaponTypes::None : targetType.groundWeapon() != BWAPI::WeaponTypes::None;

    //if (target->getType().isWorker())
    //{
        //isThreat = false;
    //}

    if (target->getType() == BWAPI::UnitTypes::Zerg_Larva || target->getType() == BWAPI::UnitTypes::Zerg_Egg)
    {
        return 0;
    }

    if (rangedUnit->isFlying() && target->getType() == BWAPI::UnitTypes::Protoss_Carrier)
    {
        return 101;
    }

    

    // if the target is building something near our base something is fishy
    BWAPI::Position ourBasePosition = BWAPI::Position(BWAPI::Broodwar->self()->getStartLocation());
    if (target->getType().isWorker() && (target->isConstructing() || target->isRepairing()) && target->getDistance(ourBasePosition) < 1200)
    {
        return 100;
    }

    if (target->getType().isBuilding() && (target->isCompleted() || target->isBeingConstructed()) && target->getDistance(ourBasePosition) < 1200)
    {
        return 90;
    }

    // highest priority is something that can attack us or aid in combat
    if (targetType == BWAPI::UnitTypes::Terran_Bunker || isThreat)
    {
        return 11;
    }
    // next priority is worker
    else if (targetType.isWorker())
    {
        if (rangedUnit->getType() == BWAPI::UnitTypes::Terran_Vulture)
        {
            return 11;
        }

        return 11;
    }
    // next is special buildings
    else if (targetType == BWAPI::UnitTypes::Zerg_Spawning_Pool)
    {
        return 5;
    }
    // next is special buildings
    else if (targetType == BWAPI::UnitTypes::Protoss_Pylon)
    {
        return 5;
    }
    // next is buildings that cost gas
    else if (targetType.gasPrice() > 0)
    {
        return 4;
    }
    else if (targetType.mineralPrice() > 0)
    {
        return 3;
    }
    // then everything else
    else
    {
        return 1;
    }
}

BWAPI::Unit WraithManager::closestrangedUnit(BWAPI::Unit target, std::set<BWAPI::Unit>& rangedUnitsToAssign)
{
    double minDistance = 0;
    BWAPI::Unit closest = nullptr;

    for (auto& rangedUnit : rangedUnitsToAssign)
    {
        double distance = rangedUnit->getDistance(target);
        if (!closest || distance < minDistance)
        {
            minDistance = distance;
            closest = rangedUnit;
        }
    }

    return closest;
}






