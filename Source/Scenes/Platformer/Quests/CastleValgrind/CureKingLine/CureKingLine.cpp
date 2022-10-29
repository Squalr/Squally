#include "CureKingLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/CastleValgrind/CureKingLine/DefeatAgnes.h"
#include "Scenes/Platformer/Quests/CastleValgrind/CureKingLine/TalkToMabel.h"
#include "Scenes/Platformer/Quests/CastleValgrind/CureKingLine/UnhauntCastle.h"

using namespace cocos2d;

const std::string CureKingLine::MapKeyQuestLine = "cure-king";

CureKingLine* CureKingLine::create()
{
	CureKingLine* instance = new CureKingLine();

	instance->autorelease();

	return instance;
}

CureKingLine::CureKingLine() : super(CureKingLine::MapKeyQuestLine,
	{
		QuestData(TalkToMabel::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return TalkToMabel::create(owner, questLine); }),
		QuestData(UnhauntCastle::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return UnhauntCastle::create(owner, questLine); }),
		QuestData(DefeatAgnes::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return DefeatAgnes::create(owner, questLine); }),
	})
{
}

CureKingLine::~CureKingLine()
{
}

QuestLine* CureKingLine::clone()
{
	return CureKingLine::create();
}
