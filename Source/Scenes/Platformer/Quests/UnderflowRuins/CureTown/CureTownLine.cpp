#include "CureTownLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/CureTown/ArriveInAthens.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/CureTown/LowerRope.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/CureTown/TalkToAphrodite.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/CureTown/TalkToHera.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/CureTown/TalkToZeus.h"

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
	QuestData(ArriveInAthens::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return ArriveInAthens::create(owner, questLine); }),
	QuestData(TalkToHera::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return TalkToHera::create(owner, questLine); }),
	QuestData(LowerRope::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return LowerRope::create(owner, questLine); }),
	QuestData(TalkToZeus::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return TalkToZeus::create(owner, questLine); }),
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
