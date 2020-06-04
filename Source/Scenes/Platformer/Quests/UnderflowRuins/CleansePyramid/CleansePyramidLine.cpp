#include "CleansePyramidLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/CleansePyramid/DefeatOsiris.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/CleansePyramid/TalkToCleopatra.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/CleansePyramid/UnlockTomb.h"

using namespace cocos2d;

const std::string CleansePyramidLine::MapKeyQuestLine = "cleanse-pyramid";

CleansePyramidLine* CleansePyramidLine::create()
{
	CleansePyramidLine* instance = new CleansePyramidLine();

	instance->autorelease();

	return instance;
}

CleansePyramidLine::CleansePyramidLine() : super(CleansePyramidLine::MapKeyQuestLine, {
	QuestData(DefeatOsiris::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return DefeatOsiris::create(owner, questLine); }),
	QuestData(UnlockTomb::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return UnlockTomb::create(owner, questLine); }),
	QuestData(TalkToCleopatra::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return TalkToCleopatra::create(owner, questLine); }),
})
{
}

CleansePyramidLine::~CleansePyramidLine()
{
}

QuestLine* CleansePyramidLine::clone()
{
	return CleansePyramidLine::create();
}
