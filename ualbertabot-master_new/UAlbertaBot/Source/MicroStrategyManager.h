#pragma once

#include "Common.h"
#include "BuildOrder.h"

namespace UAlbertaBot
{
	class MicroStrategyManager
	{
		friend class Global;

		MicroStrategyManager();


		BWAPI::Race					    m_selfRace;
		BWAPI::Race					    m_enemyRace;
		BuildOrder                      m_emptyBuildOrder;

		//bool first_time_detect_zerg_lurker = true;
		bool Zerg_lurker_has_been_found = false;

		//const MetaPairVector  getForLurkerBuildOrderGoal() const;
		


	public:
		void update();
		bool detect_Zerg_Lurker();
		//bool confirm_Zerg_Lurker();

		//const MetaPairVector  getForLurkerBuildOrderGoal() const;
		//void  getForLurkerBuildOrderGoal(std::vector<MetaPair> goal);

	};

}