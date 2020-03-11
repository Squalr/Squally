#include "SneakIntoLianasHouseLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/SneakIntoLianasHouse/LianaDoorLocked.h"
#include "Scenes/Platformer/Quests/EndianForest/SneakIntoLianasHouse/SneakIntoLianasHouse.h"

using namespace cocos2d;

const std::string SneakIntoLianasHouseLine::MapKeyQuestLine = "sneak-liana-line";

SneakIntoLianasHouseLine* SneakIntoLianasHouseLine::create()
{
	SneakIntoLianasHouseLine* instance = new SneakIntoLianasHouseLine();

	instance->autorelease();

	return instance;
}

SneakIntoLianasHouseLine::SneakIntoLianasHouseLine() : super(SneakIntoLianasHouseLine::MapKeyQuestLine,
	{
		QuestData(LianaDoorLocked::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return LianaDoorLocked::create(owner, questLine); }),
		QuestData(SneakIntoLianasHouse::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return SneakIntoLianasHouse::create(owner, questLine); }),
	})
{
}

SneakIntoLianasHouseLine::~SneakIntoLianasHouseLine()
{
}

QuestLine* SneakIntoLianasHouseLine::clone()
{
	return SneakIntoLianasHouseLine::create();
}
