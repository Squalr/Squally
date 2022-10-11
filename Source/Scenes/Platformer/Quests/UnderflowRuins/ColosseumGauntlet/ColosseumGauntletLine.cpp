#include "ColosseumGauntletLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/ColosseumGauntlet/GauntletIntroduction.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/ColosseumGauntlet/WinGauntlet.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/ColosseumGauntlet/TalkToCleopatra.h"

using namespace cocos2d;

const std::string ColosseumGauntletLine::MapKeyQuestLine = "colosseum-gauntlet";

ColosseumGauntletLine* ColosseumGauntletLine::create()
{
	ColosseumGauntletLine* instance = new ColosseumGauntletLine();

	instance->autorelease();

	return instance;
}

ColosseumGauntletLine::ColosseumGauntletLine() : super(ColosseumGauntletLine::MapKeyQuestLine, {
	QuestData(GauntletIntroduction::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return GauntletIntroduction::create(owner, questLine); }),
	QuestData(WinGauntlet::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return WinGauntlet::create(owner, questLine); }),
	QuestData(TalkToCleopatra::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return TalkToCleopatra::create(owner, questLine); }),
})
{
}

ColosseumGauntletLine::~ColosseumGauntletLine()
{
}

QuestLine* ColosseumGauntletLine::clone()
{
	return ColosseumGauntletLine::create();
}
