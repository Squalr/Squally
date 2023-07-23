
#include "ReleasePressureLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/FirewallFissure/ReleasePressure/LavaEscape.h"
#include "Scenes/Platformer/Quests/FirewallFissure/ReleasePressure/ReleasePressure.h"
#include "Scenes/Platformer/Quests/FirewallFissure/ReleasePressure/WelcomeToFirewall.h"

using namespace cocos2d;

const std::string ReleasePressureLine::MapKeyQuestLine = "release-pressure";

ReleasePressureLine* ReleasePressureLine::create()
{
	ReleasePressureLine* instance = new ReleasePressureLine();

	instance->autorelease();

	return instance;
}

ReleasePressureLine::ReleasePressureLine() : super(ReleasePressureLine::MapKeyQuestLine, {
	QuestData(WelcomeToFirewall::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return WelcomeToFirewall::create(owner, questLine); }),
	QuestData(LavaEscape::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return LavaEscape::create(owner, questLine); }),
	QuestData(ReleasePressure::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return ReleasePressure::create(owner, questLine); }),
})
{
}

ReleasePressureLine::~ReleasePressureLine()
{
}

QuestLine* ReleasePressureLine::clone()
{
	return ReleasePressureLine::create();
}
