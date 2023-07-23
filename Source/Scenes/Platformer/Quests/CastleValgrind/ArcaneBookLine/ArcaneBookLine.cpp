#include "ArcaneBookLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/CastleValgrind/CureKingLine/CureKingLine.h"
#include "Scenes/Platformer/Quests/CastleValgrind/CureKingLine/UnhauntCastle.h"
#include "Scenes/Platformer/Quests/CastleValgrind/ArcaneBookLine/TakeArcaneBook.h"

using namespace cocos2d;

const std::string ArcaneBookLine::MapKeyQuestLine = "arcane-book";

ArcaneBookLine* ArcaneBookLine::create()
{
	ArcaneBookLine* instance = new ArcaneBookLine();

	instance->autorelease();

	return instance;
}

ArcaneBookLine::ArcaneBookLine() : super(ArcaneBookLine::MapKeyQuestLine,
	{
		QuestData(TakeArcaneBook::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return TakeArcaneBook::create(owner, questLine); }),
	})
{
}

ArcaneBookLine::~ArcaneBookLine()
{
}

QuestLine* ArcaneBookLine::clone()
{
	return ArcaneBookLine::create();
}
