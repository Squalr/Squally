
#include "DefeatRhinomanLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/DataMines/DefeatRhinoman/DefeatRhinoman.h"

using namespace cocos2d;

const std::string DefeatRhinomanLine::MapKeyQuestLine = "defeat-rhinoman";

DefeatRhinomanLine* DefeatRhinomanLine::create()
{
	DefeatRhinomanLine* instance = new DefeatRhinomanLine();

	instance->autorelease();

	return instance;
}

DefeatRhinomanLine::DefeatRhinomanLine() : super(DefeatRhinomanLine::MapKeyQuestLine, {
	QuestData(DefeatRhinoman::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return DefeatRhinoman::create(owner, questLine); }),
})
{
}

DefeatRhinomanLine::~DefeatRhinomanLine()
{
}

QuestLine* DefeatRhinomanLine::clone()
{
	return DefeatRhinomanLine::create();
}
