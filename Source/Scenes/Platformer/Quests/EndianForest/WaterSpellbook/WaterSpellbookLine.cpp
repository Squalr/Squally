#include "WaterSpellbookLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/WaterSpellbook/WaterSpellbook.h"

using namespace cocos2d;

const std::string WaterSpellbookLine::MapKeyQuestLine = "water-spellbook";

WaterSpellbookLine* WaterSpellbookLine::create()
{
	WaterSpellbookLine* instance = new WaterSpellbookLine();

	instance->autorelease();

	return instance;
}

WaterSpellbookLine::WaterSpellbookLine() : super(WaterSpellbookLine::MapKeyQuestLine,
	{
		QuestData(WaterSpellbook::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return WaterSpellbook::create(owner, questLine); }),
	})
{
}

WaterSpellbookLine::~WaterSpellbookLine()
{
}

QuestLine* WaterSpellbookLine::clone()
{
	return WaterSpellbookLine::create();
}
