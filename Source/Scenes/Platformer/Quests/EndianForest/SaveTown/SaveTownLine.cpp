#include "SaveTownLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/FindElrielLine.h"
#include "Scenes/Platformer/Quests/EndianForest/SaveTown/TalkToMages.h"
#include "Scenes/Platformer/Quests/EndianForest/SaveTown/RepairRam.h"

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
		QuestData(RepairRam::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return RepairRam::create(owner, questLine); }),
	}) // ,
	// (QuestLine*)FindElrielLine::create())
{
}

SaveTownLine::~SaveTownLine()
{
}

QuestLine* SaveTownLine::clone()
{
	return SaveTownLine::create();
}
