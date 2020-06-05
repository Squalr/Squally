#include "RestoreWarpGatesLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/Global/PowerWarpGateBP.h"
#include "Scenes/Platformer/Quests/Global/PowerWarpGateCV.h"
#include "Scenes/Platformer/Quests/Global/PowerWarpGateDH.h"
#include "Scenes/Platformer/Quests/Global/PowerWarpGateDM.h"
#include "Scenes/Platformer/Quests/Global/PowerWarpGateEF.h"
#include "Scenes/Platformer/Quests/Global/PowerWarpGateLC.h"
#include "Scenes/Platformer/Quests/Global/PowerWarpGateUR.h"
#include "Scenes/Platformer/Quests/Global/PowerWarpGateVS.h"

using namespace cocos2d;

const std::string RestoreWarpGatesLine::MapKeyQuestLine = "restore-warp-gates";

RestoreWarpGatesLine* RestoreWarpGatesLine::create()
{
	RestoreWarpGatesLine* instance = new RestoreWarpGatesLine();

	instance->autorelease();

	return instance;
}

RestoreWarpGatesLine::RestoreWarpGatesLine() : super(RestoreWarpGatesLine::MapKeyQuestLine, {
	QuestData(PowerWarpGateBP::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return PowerWarpGateBP::create(owner, questLine); }),
	QuestData(PowerWarpGateCV::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return PowerWarpGateCV::create(owner, questLine); }),
	QuestData(PowerWarpGateDH::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return PowerWarpGateDH::create(owner, questLine); }),
	QuestData(PowerWarpGateDM::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return PowerWarpGateDM::create(owner, questLine); }),
	QuestData(PowerWarpGateEF::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return PowerWarpGateEF::create(owner, questLine); }),
	QuestData(PowerWarpGateLC::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return PowerWarpGateLC::create(owner, questLine); }),
	QuestData(PowerWarpGateUR::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return PowerWarpGateUR::create(owner, questLine); }),
	QuestData(PowerWarpGateVS::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return PowerWarpGateVS::create(owner, questLine); }),
})
{
}

RestoreWarpGatesLine::~RestoreWarpGatesLine()
{
}

QuestLine* RestoreWarpGatesLine::clone()
{
	return RestoreWarpGatesLine::create();
}
