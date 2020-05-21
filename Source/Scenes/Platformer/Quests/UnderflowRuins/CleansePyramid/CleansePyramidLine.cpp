#include "CleansePyramidLine.h"

#include "Engine/Quests/QuestTask.h"
// #include "Scenes/Platformer/Quests/UnderflowRuins/CureTown/SneakPastLycan.h"

using namespace cocos2d;

const std::string CleansePyramidLine::MapKeyQuestLine = "cleanse-pyramid";

CleansePyramidLine* CleansePyramidLine::create()
{
	CleansePyramidLine* instance = new CleansePyramidLine();

	instance->autorelease();

	return instance;
}

CleansePyramidLine::CleansePyramidLine() : super(CleansePyramidLine::MapKeyQuestLine, {
	// QuestData(SneakPastLycan::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return SneakPastLycan::create(owner, questLine); }),
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
