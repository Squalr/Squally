#include "WindSpellbookLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/FindElrielLine.h"
#include "Scenes/Platformer/Quests/EndianForest/WindSpellbook/WindSpellbook.h"

using namespace cocos2d;

const std::string WindSpellbookLine::MapKeyQuestLine = "wind-spellbook";

WindSpellbookLine* WindSpellbookLine::create()
{
	WindSpellbookLine* instance = new WindSpellbookLine();

	instance->autorelease();

	return instance;
}

WindSpellbookLine::WindSpellbookLine() : super(WindSpellbookLine::MapKeyQuestLine,
	{
		QuestData(WindSpellbook::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return WindSpellbook::create(owner, questLine); }),
	},
	(QuestLine*)FindElrielLine::create())
{
}

WindSpellbookLine::~WindSpellbookLine()
{
}

QuestLine* WindSpellbookLine::clone()
{
	return WindSpellbookLine::create();
}
