#include "CureTownLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/CureTown/TalkToAphrodite.h"

using namespace cocos2d;

const std::string CureTownLine::MapKeyQuestLine = "cure-town";

CureTownLine* CureTownLine::create()
{
	CureTownLine* instance = new CureTownLine();

	instance->autorelease();

	return instance;
}

CureTownLine::CureTownLine() : super(CureTownLine::MapKeyQuestLine, {
	QuestData(TalkToAphrodite::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return TalkToAphrodite::create(owner, questLine); }),
})
{
}

CureTownLine::~CureTownLine()
{
}

QuestLine* CureTownLine::clone()
{
	return CureTownLine::create();
}
