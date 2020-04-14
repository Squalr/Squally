#include "SaveTownLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/FindElrielLine.h"
#include "Scenes/Platformer/Quests/EndianForest/SaveTown/AfterFight.h"
#include "Scenes/Platformer/Quests/EndianForest/SaveTown/FightGorgon.h"
#include "Scenes/Platformer/Quests/EndianForest/SaveTown/RepairRam.h"
#include "Scenes/Platformer/Quests/EndianForest/SaveTown/ReturnToQueenAgain.h"
#include "Scenes/Platformer/Quests/EndianForest/SaveTown/TalkToMages.h"

using namespace cocos2d;

const std::string SaveTownLine::MapKeyQuestLine = "save-town";

SaveTownLine* SaveTownLine::create()
{
	SaveTownLine* instance = new SaveTownLine();

	instance->autorelease();

	return instance;
}

SaveTownLine::SaveTownLine() : super(SaveTownLine::MapKeyQuestLine,
	{
		QuestData(TalkToMages::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return TalkToMages::create(owner, questLine); }),
		QuestData(RepairRam::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return RepairRam::create(owner, questLine); }),
		QuestData(FightGorgon::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return FightGorgon::create(owner, questLine); }),
		QuestData(AfterFight::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return AfterFight::create(owner, questLine); }),
		QuestData(ReturnToQueenAgain::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return ReturnToQueenAgain::create(owner, questLine); }),
	})
{
}

SaveTownLine::~SaveTownLine()
{
}

QuestLine* SaveTownLine::clone()
{
	return SaveTownLine::create();
}
