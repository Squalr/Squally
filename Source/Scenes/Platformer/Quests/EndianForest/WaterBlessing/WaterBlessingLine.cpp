#include "WaterBlessingLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/WaterBlessing/WaterBlessing.h"

using namespace cocos2d;

const std::string WaterBlessingLine::MapKeyQuestLine = "water-blessing";

WaterBlessingLine* WaterBlessingLine::create()
{
	WaterBlessingLine* instance = new WaterBlessingLine();

	instance->autorelease();

	return instance;
}

WaterBlessingLine::WaterBlessingLine() : super(WaterBlessingLine::MapKeyQuestLine,
	{
		QuestData(WaterBlessing::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return WaterBlessing::create(owner, questLine); }),
	})
{
}

WaterBlessingLine::~WaterBlessingLine()
{
}

QuestLine* WaterBlessingLine::clone()
{
	return WaterBlessingLine::create();
}
