#include "RestorePowerLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/DataMines/RestorePower/RestorePower.h"
#include "Scenes/Platformer/Quests/DataMines/RestorePower/TalkToOlive.h"
#include "Scenes/Platformer/Quests/DataMines/RestorePower/TalkToPrincessDawn.h"

using namespace cocos2d;

const std::string RestorePowerLine::MapKeyQuestLine = "restore-power";

RestorePowerLine* RestorePowerLine::create()
{
	RestorePowerLine* instance = new RestorePowerLine();

	instance->autorelease();

	return instance;
}

RestorePowerLine::RestorePowerLine() : super(RestorePowerLine::MapKeyQuestLine, {
	QuestData(TalkToOlive::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return TalkToOlive::create(owner, questLine); }),
	QuestData(TalkToPrincessDawn::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return TalkToPrincessDawn::create(owner, questLine); }),
	QuestData(RestorePower::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return RestorePower::create(owner, questLine); }),
})
{
}

RestorePowerLine::~RestorePowerLine()
{
}

QuestLine* RestorePowerLine::clone()
{
	return RestorePowerLine::create();
}
