#include "TerranDropManager.h"
#include "BaseLocationManager.h"
#include "Global.h"
#include "Micro.h"
#include "UnitUtil.h"
#include "MapTools.h"


using namespace UAlbertaBot;

TerranDropManager::TerranDropManager()
{
}

void TerranDropManager::executeMicro(const BWAPI::Unitset& targets)
{
    const BWAPI::Unitset& transportUnits = getUnits();

    if (transportUnits.empty())
    {
        return;
    }

    
}

void TerranDropManager::update()
{
    //bool loadUnitsBool = false;
    //int dropUnitsNum = 0;


    const BWAPI::Unitset& terranDropUnits = getUnits();

    if (!m_dropShip)
    {
        for (auto& units : terranDropUnits)
        {
            if (units->getType() == BWAPI::UnitTypes::Terran_Dropship)
            {
                m_dropShip = units;
                //availableDropShips.insert(units);
                BWAPI::Broodwar->drawTextScreen(430, 190, "Terran_Dropship");
            }
        }
    }
   


    if (!m_dropShip)
    {
        //BWAPI::Broodwar->drawTextScreen(430, 250, "DropShipsdetect conduct");
        return;
    }

    if (dropShipreturning == true)
    {
        //BWAPI::Broodwar->drawTextScreen(430, 230, "dropShiping conduct");
        return;
    }
    if (dropOnce == true)
    {
        //BWAPI::Broodwar->drawTextScreen(430, 240, "dropOnce conduct");
        return;
    }


    /*if (!availableDropUnits.empty() && dropUnitsNum != 4)
    {
        for (auto& units : availableDropUnits)
        {
            availableDropUnits.erase(units);
        }
        dropUnitsNum = 0;
    }*/

    if (!terranDropUnits.empty() && !availableDropUnitsFinished)
    {
        for (auto& units : terranDropUnits)
        {
            /*if (dropUnitsNum == 4)
            {
                break;
            }*/
            
            if (units->getType() == BWAPI::UnitTypes::Terran_Firebat)
            {
                availableDropUnits.insert(units);
                dropUnitsNum += 1;
                BWAPI::Broodwar->drawTextScreen(430, 200, "Terran_Firebat");
            }
        }
    }

    /*if (!m_dropShip)
    {
        return;
    }
    if (dropUnitsNum < 4)
    {
        return;
    }*/
    
    /*if (true == loadUnits(availableDropUnits, dropUnitsNum))
    {
        if (m_mapEdgeVertices.empty())
        {
            calculateMapEdgeVertices();
        }

        moveTransport();
        moveTroops();
    }*/
    BWAPI::Broodwar->drawTextScreen(430, 180, "dropUnitsNum: %d", dropUnitsNum);
    if (availableDropUnits.size() == 4)
    {
        availableDropUnitsFinished = true;
    }
    

    //下次可能改动地方
    if (availableDropUnits.size() == 4 && dropShipreturning == false)
    {
        loadUnits(availableDropUnits, dropUnitsNum);
    }
    

    if (m_mapEdgeVertices.empty())
    {
        calculateMapEdgeVertices();
    }


    /*if (shipToEnemyBase_ing == true)
    {
        return;
    }*/
    //dropUnitsNum = 0;
    //for (auto& units : availableDropShips)
    //{
    BWAPI::Broodwar->drawTextScreen(430, 210, "availableDropShips for");
    if (m_dropShip->getSpaceRemaining() == 4)
    {
        //for (;;)
        //{
            moveTransport();
            moveTroops();
            //if (m_dropShip->getSpaceRemaining() == 0)
            //{
                //break;
            //}
        //}
        //moveTransport();
        //moveTroops();
    }
    //moveTransport();
    
    //}
    //moveTransport();
    /*if (troopsAtEnemyBase_ing == true)
    {
        return;
    }*/
    //moveTroops();
    //drawTransportInformation();
    
}

void TerranDropManager::drawTransportInformation(int x = 0, int y = 0)
{
    if (!Config::Debug::DrawUnitTargetInfo)
    {
        return;
    }

    for (size_t i(0); i < m_mapEdgeVertices.size(); ++i)
    {
        BWAPI::Broodwar->drawCircleMap(m_mapEdgeVertices[i], 4, BWAPI::Colors::Green, false);
        BWAPI::Broodwar->drawTextMap(m_mapEdgeVertices[i], "%d", i);
    }
}

void TerranDropManager::loadUnits(BWAPI::Unitset availableDropUnits, int num)
{
    //int loadCount = 0;
    BWAPI::Broodwar->drawTextScreen(430, 160, "load Units processing");

    //if (availableDropUnits.empty())
        //return;
    //for (auto& shipunits : availableDropShips)
    //{
        //if(shipunits->exists() && (shipunits->getSpaceRemaining() >=0 ))
        for (auto& dropunits : availableDropUnits)
        {
            loadCount += 1;
            //units->rightClick(m_dropShip);
            //units->move(m_dropShip->getPosition());
            //units->rightClick(m_dropShip);
            BWAPI::Broodwar->drawTextScreen(430, 170, "load count: %d", loadCount);
            //m_dropShip->move(units->getPosition());
            m_dropShip->load(dropunits);
            //if (m_dropShip->getLoadedUnits().size() == loadCount)//确保上船不冲突
            //{
            //    continue;
            //}
            /*BWAPI::UnitCommand currentCommand(m_dropShip->getLastCommand());
            if ((currentCommand.getType() == BWAPI::UnitCommandTypes::Load)
                && m_dropShip->getLoadedUnits().size() != loadCount)
            {
                return;
            }*/
        }
    //}

}

void TerranDropManager::moveTransport()
{
    if (!m_dropShip || !m_dropShip->exists() || !(m_dropShip->getHitPoints() > 0))
    {
        return;
    }

    shipToEnemyBase_ing = true;
    // If I didn't finish unloading the troops, wait
    BWAPI::UnitCommand currentCommand(m_dropShip->getLastCommand());
    if ((currentCommand.getType() == BWAPI::UnitCommandTypes::Unload_All
        || currentCommand.getType() == BWAPI::UnitCommandTypes::Unload_All_Position)
        && m_dropShip->getLoadedUnits().size() > 0)
    {
        return;
    }

    if (m_to.isValid() && m_from.isValid())
    {
        followPerimeter(m_to, m_from);
    }
    else
    {
        followPerimeter();
    }
}

void TerranDropManager::moveTroops()
{
    if (!m_dropShip || !m_dropShip->exists() || !(m_dropShip->getHitPoints() > 0))
    {
        return;
    }
    BWAPI::Broodwar->drawTextScreen(430, 270, "moveTroops conduct");


    
    //BWAPI::Unitset rangedUnits;

    //unload zealots if close enough or dying
    int transportHP = m_dropShip->getHitPoints() + m_dropShip->getShields();

    auto enemyBaseLocation = Global::Bases().getPlayerStartingBaseLocation(BWAPI::Broodwar->enemy());
    auto myBaseLocation = Global::Bases().getPlayerStartingBaseLocation(BWAPI::Broodwar->self());

    if ((enemyBaseLocation && (m_dropShip->getDistance(enemyBaseLocation->getPosition()) < 400 )|| transportHP < 100)
        && m_dropShip->canUnloadAtPosition(m_dropShip->getPosition()))
    {
        //unload troops 
        //and return? 

        // get the unit's current command
        BWAPI::UnitCommand currentCommand(m_dropShip->getLastCommand());

        // if we've already told this unit to unload, wait
        /*if (m_dropShip->getHitPoints() < 75)
        {
            m_dropShip->move(myBaseLocation->getPosition());
            transportstop = true;
        }*/
        if ((currentCommand.getType() == BWAPI::UnitCommandTypes::Unload_All || currentCommand.getType() == BWAPI::UnitCommandTypes::Unload_All_Position))
        {
            return;
        }
        



        //else unload
        //if (!dropShipreturning)
        //{
            //m_dropShip->unloadAll(m_dropShip->getPosition());
        //}

        //for (;;)
        //{
        m_dropShip->unloadAll(m_dropShip->getPosition());
            //if (m_dropShip->getSpaceRemaining() == 8)
            //{
                //break;
            //}
        //}
        
        BWAPI::Broodwar->drawTextScreen(430, 260, "unloadAll return");
        assignTargetsOld(availableDropUnits);
        if (m_dropShip->getSpaceRemaining() == 8)
        {
            m_dropShip->move(myBaseLocation->getPosition());
            dropShipreturning = true;
        }
    }
    //availableDropUnits.clear();

    //afterDropUnits =  m_dropShip->getUnitsInRadius(350, BWAPI::Filter::IsOwned && !BWAPI::Filter::IsFlying);
    //m_dropShip->move(myBaseLocation->getPosition());

    //m_rangedManager.setUnits(afterDropUnits);
    //afterDropUnits.clear();
    /*if ((m_dropShip->getSpaceRemaining() == 8 && m_dropShip->getDistance(enemyBaseLocation->getPosition() ) < 1000))//自己写的
    {
        BWAPI::Broodwar->drawTextScreen(430, 220, "DropShips return");
        m_dropShip->move(myBaseLocation->getPosition());
        assignTargetsOld(availableDropUnits);
        dropShipreturning = true;
    }*/

    
    /*if (m_dropShip->getDistance(myBaseLocation->getPosition()) < 500 && dropShipreturning == true)
    {
        dropShipreturning = false;
        dropOnce = true;
    }*/

    


}

void TerranDropManager::followPerimeter(int clockwise)
{
    BWAPI::Position goTo = getFleePosition(clockwise);

    if (Config::Debug::DrawUnitTargetInfo)
    {
        BWAPI::Broodwar->drawCircleMap(goTo, 5, BWAPI::Colors::Red, true);
    }

    Micro::SmartMove(m_dropShip, goTo);
}

void TerranDropManager::followPerimeter(BWAPI::Position to, BWAPI::Position from)
{
    static int following = 0;
    if (following)
    {
        followPerimeter(following);
        return;
    }

    //assume we're near FROM! 
    if (m_dropShip->getDistance(from) < 50 && m_waypoints.empty())
    {
        //compute waypoints
        std::pair<int, int> wpIDX = findSafePath(to, from);
        bool valid = (wpIDX.first > -1 && wpIDX.second > -1);
        UAB_ASSERT_WARNING(valid, "waypoints not valid! (transport mgr)");
        m_waypoints.push_back(m_mapEdgeVertices[wpIDX.first]);
        m_waypoints.push_back(m_mapEdgeVertices[wpIDX.second]);

        BWAPI::Broodwar->printf("WAYPOINTS: [%d] - [%d]", wpIDX.first, wpIDX.second);

        Micro::SmartMove(m_dropShip, m_waypoints[0]);
    }
    else if (m_waypoints.size() > 1 && m_dropShip->getDistance(m_waypoints[0]) < 100)
    {
        BWAPI::Broodwar->printf("FOLLOW PERIMETER TO SECOND WAYPOINT!");
        //follow perimeter to second waypoint! 
        //clockwise or counterclockwise? 
        int closestPolygonIndex = getClosestVertexIndex(m_dropShip);
        UAB_ASSERT_WARNING(closestPolygonIndex != -1, "Couldn't find a closest vertex");

        if (m_mapEdgeVertices[(closestPolygonIndex + 1) % m_mapEdgeVertices.size()].getApproxDistance(m_waypoints[1]) <
            m_mapEdgeVertices[(closestPolygonIndex - 1) % m_mapEdgeVertices.size()].getApproxDistance(m_waypoints[1]))
        {
            BWAPI::Broodwar->printf("FOLLOW clockwise");
            following = 1;
            followPerimeter(following);
        }
        else
        {
            BWAPI::Broodwar->printf("FOLLOW counter clockwise");
            following = -1;
            followPerimeter(following);
        }

    }
    else if (m_waypoints.size() > 1 && m_dropShip->getDistance(m_waypoints[1]) < 50)
    {
        //if close to second waypoint, go to destination!
        following = 0;
        Micro::SmartMove(m_dropShip, to);
    }

}


int TerranDropManager::getClosestVertexIndex(BWAPI::UnitInterface* unit)
{
    int closestIndex = -1;
    double closestDistance = 10000000;

    for (size_t i(0); i < m_mapEdgeVertices.size(); ++i)
    {
        double dist = unit->getDistance(m_mapEdgeVertices[i]);
        if (dist < closestDistance)
        {
            closestDistance = dist;
            closestIndex = i;
        }
    }

    return closestIndex;
}

int TerranDropManager::getClosestVertexIndex(BWAPI::Position p)
{
    int closestIndex = -1;
    double closestDistance = 10000000;

    for (size_t i(0); i < m_mapEdgeVertices.size(); ++i)
    {

        double dist = p.getApproxDistance(m_mapEdgeVertices[i]);
        if (dist < closestDistance)
        {
            closestDistance = dist;
            closestIndex = i;
        }
    }

    return closestIndex;
}

std::pair<int, int> TerranDropManager::findSafePath(BWAPI::Position to, BWAPI::Position from)
{
    BWAPI::Broodwar->printf("FROM: [%d,%d]", from.x, from.y);
    BWAPI::Broodwar->printf("TO: [%d,%d]", to.x, to.y);

    //closest map edge point to destination
    int endPolygonIndex = getClosestVertexIndex(to);
    //BWAPI::Broodwar->printf("end indx: [%d]", endPolygonIndex);

    UAB_ASSERT_WARNING(endPolygonIndex != -1, "Couldn't find a closest vertex");
    BWAPI::Position enemyEdge = m_mapEdgeVertices[endPolygonIndex];

    auto* enemyBaseLocation = Global::Bases().getPlayerStartingBaseLocation(BWAPI::Broodwar->enemy());
    BWAPI::Position enemyPosition = enemyBaseLocation->getPosition();

    //find the projections on the 4 edges
    UAB_ASSERT_WARNING((m_minCorner.isValid() && m_maxCorner.isValid()), "Map corners should have been set! (transport mgr)");
    std::vector<BWAPI::Position> p;
    p.push_back(BWAPI::Position(from.x, m_minCorner.y));
    p.push_back(BWAPI::Position(from.x, m_maxCorner.y));
    p.push_back(BWAPI::Position(m_minCorner.x, from.y));
    p.push_back(BWAPI::Position(m_maxCorner.x, from.y));

    int d1 = p[0].getApproxDistance(enemyPosition);
    int d2 = p[1].getApproxDistance(enemyPosition);
    int d3 = p[2].getApproxDistance(enemyPosition);
    int d4 = p[3].getApproxDistance(enemyPosition);

    //have to choose the two points that are not max or min (the sides!)
    int maxIndex = (d1 > d2 ? d1 : d2) > (d3 > d4 ? d3 : d4) ?
        (d1 > d2 ? 0 : 1) : (d3 > d4 ? 2 : 3);

    int minIndex = (d1 < d2 ? d1 : d2) < (d3 < d4 ? d3 : d4) ?
        (d1 < d2 ? 0 : 1) : (d3 < d4 ? 2 : 3);

    if (maxIndex > minIndex)
    {
        p.erase(p.begin() + maxIndex);
        p.erase(p.begin() + minIndex);
    }
    else
    {
        p.erase(p.begin() + minIndex);
        p.erase(p.begin() + maxIndex);
    }

    //get the one that works best from the two.
    BWAPI::Position waypoint = (enemyEdge.getApproxDistance(p[0]) < enemyEdge.getApproxDistance(p[1])) ? p[0] : p[1];

    int startPolygonIndex = getClosestVertexIndex(waypoint);

    return std::pair<int, int>(startPolygonIndex, endPolygonIndex);

}

BWAPI::Position TerranDropManager::getFleePosition(int clockwise)
{
    UAB_ASSERT_WARNING(!m_mapEdgeVertices.empty(), "We should have a transport route!");

    // if this is the first flee, we will not have a previous perimeter index
    if (m_currentRegionVertexIndex == -1)
    {
        // so return the closest position in the polygon
        int closestPolygonIndex = getClosestVertexIndex(m_dropShip);

        UAB_ASSERT_WARNING(closestPolygonIndex != -1, "Couldn't find a closest vertex");

        if (closestPolygonIndex == -1)
        {
            return BWAPI::Position(BWAPI::Broodwar->self()->getStartLocation());
        }
        else
        {
            // set the current index so we know how to iterate if we are still fleeing later
            m_currentRegionVertexIndex = closestPolygonIndex;
            return m_mapEdgeVertices[closestPolygonIndex];
        }
    }
    // if we are still fleeing from the previous frame, get the next location if we are close enough
    else
    {
        double distanceFromCurrentVertex = m_mapEdgeVertices[m_currentRegionVertexIndex].getDistance(m_dropShip->getPosition());

        // keep going to the next vertex in the perimeter until we get to one we're far enough from to issue another move command
        while (distanceFromCurrentVertex < 128 * 2)
        {
            m_currentRegionVertexIndex = (m_currentRegionVertexIndex + clockwise * 1) % m_mapEdgeVertices.size();

            distanceFromCurrentVertex = m_mapEdgeVertices[m_currentRegionVertexIndex].getDistance(m_dropShip->getPosition());
        }

        return m_mapEdgeVertices[m_currentRegionVertexIndex];
    }

}

void TerranDropManager::calculateMapEdgeVertices()
{
    auto enemyBaseLocation = Global::Bases().getPlayerStartingBaseLocation(BWAPI::Broodwar->enemy());

    if (!enemyBaseLocation)
    {
        return;
    }

    const BWAPI::Position basePosition = BWAPI::Position(BWAPI::Broodwar->self()->getStartLocation());
    const std::vector<BWAPI::TilePosition>& closestTobase = Global::Map().getClosestTilesTo(basePosition);

    std::set<BWAPI::Position> unsortedVertices;

    int minX = std::numeric_limits<int>::max(); int minY = minX;
    int maxX = std::numeric_limits<int>::min(); int maxY = maxX;

    //compute mins and maxs
    for (auto& tile : closestTobase)
    {
        if (tile.x > maxX) maxX = tile.x;
        else if (tile.x < minX) minX = tile.x;

        if (tile.y > maxY) maxY = tile.y;
        else if (tile.y < minY) minY = tile.y;
    }

    m_minCorner = BWAPI::Position(minX, minY) * 32 + BWAPI::Position(16, 16);
    m_maxCorner = BWAPI::Position(maxX, maxY) * 32 + BWAPI::Position(16, 16);

    //add all(some) edge tiles! 
    for (int x = minX; x <= maxX; x += 5)
    {
        unsortedVertices.insert(BWAPI::Position(x, minY) * 32 + BWAPI::Position(16, 16));
        unsortedVertices.insert(BWAPI::Position(x, maxY) * 32 + BWAPI::Position(16, 16));
    }

    for (int y = minY; y <= maxY; y += 5)
    {
        unsortedVertices.insert(BWAPI::Position(minX, y) * 32 + BWAPI::Position(16, 16));
        unsortedVertices.insert(BWAPI::Position(maxX, y) * 32 + BWAPI::Position(16, 16));
    }

    std::vector<BWAPI::Position> sortedVertices;
    BWAPI::Position current = *unsortedVertices.begin();

    m_mapEdgeVertices.push_back(current);
    unsortedVertices.erase(current);

    // while we still have unsorted vertices left, find the closest one remaining to current
    while (!unsortedVertices.empty())
    {
        double bestDist = 1000000;
        BWAPI::Position bestPos;

        for (const BWAPI::Position& pos : unsortedVertices)
        {
            double dist = pos.getDistance(current);

            if (dist < bestDist)
            {
                bestDist = dist;
                bestPos = pos;
            }
        }

        current = bestPos;
        sortedVertices.push_back(bestPos);
        unsortedVertices.erase(bestPos);
    }

    m_mapEdgeVertices = sortedVertices;
}

/*void TerranDropManager::setTransportShip(BWAPI::UnitInterface* unit)
{
    m_dropShip = unit;
}*/

void TerranDropManager::setFrom(BWAPI::Position from)
{
    if (from.isValid()) { m_from = from; }
}
void TerranDropManager::setTo(BWAPI::Position to)
{
    if (to.isValid()) { m_to = to; }
}

void TerranDropManager::assignTargetsOld(BWAPI::Unitset& rangedUnits)
{
    //const BWAPI::Unitset& rangedUnits = getUnits();
    auto enemyBaseLocation = Global::Bases().getPlayerStartingBaseLocation(BWAPI::Broodwar->enemy());

    rangedUnits.move(enemyBaseLocation->getPosition());

    if (enemyBaseLocation->getGroundDistance(rangedUnits.getPosition()) < 100)
    {
        firebatTargets = rangedUnits.getUnitsInRadius(224, BWAPI::Filter::IsEnemy);

    }


    for (auto& rangedUnit : rangedUnits)
    {
        // train sub units such as scarabs or interceptors
        //trainSubUnits(rangedUnit);

        // if the order is to attack or defend
        if (m_order.getType() == SquadOrderTypes::Attack || m_order.getType() == SquadOrderTypes::Defend)
        {
            // if there are targets
            if (!firebatTargets.empty())
            {
                // find the best target for this zealot
                BWAPI::Unit target = getTarget(rangedUnit, firebatTargets);

                if (target && Config::Debug::DrawUnitTargetInfo)
                {
                    BWAPI::Broodwar->drawLineMap(rangedUnit->getPosition(), rangedUnit->getTargetPosition(), BWAPI::Colors::Purple);
                }


                // attack it
                if (Config::Micro::KiteWithRangedUnits)
                {
                    if (rangedUnit->getType() == BWAPI::UnitTypes::Zerg_Mutalisk || rangedUnit->getType() == BWAPI::UnitTypes::Terran_Vulture)
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
                if (rangedUnit->getDistance(enemyBaseLocation->getPosition()) > 150)
                {
                    // move to it
                    Micro::SmartAttackMove(rangedUnit, enemyBaseLocation->getPosition());
                }
            }
        }
    }
}

std::pair<BWAPI::Unit, BWAPI::Unit> TerranDropManager::findClosestUnitPair(const BWAPI::Unitset& attackers, const BWAPI::Unitset& targets)
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
BWAPI::Unit TerranDropManager::getTarget(BWAPI::Unit rangedUnit, const BWAPI::Unitset& targets)
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
int TerranDropManager::getAttackPriority(BWAPI::Unit rangedUnit, BWAPI::Unit target)
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

    /*if (rangedUnit->getType() == BWAPI::UnitTypes::Zerg_Overlord)
    {
        return 100;//add
    }*/

    if (rangedUnit->getType() == BWAPI::UnitTypes::Zerg_Drone)
    {
        return 100;
    }

    bool isThreat = rangedType.isFlyer() ? targetType.airWeapon() != BWAPI::WeaponTypes::None : targetType.groundWeapon() != BWAPI::WeaponTypes::None;

    if (target->getType().isWorker())
    {
        isThreat = false;
    }

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

BWAPI::Unit TerranDropManager::closestrangedUnit(BWAPI::Unit target, std::set<BWAPI::Unit>& rangedUnitsToAssign)
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







