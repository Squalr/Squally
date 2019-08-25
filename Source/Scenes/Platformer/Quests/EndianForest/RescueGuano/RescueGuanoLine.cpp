#include "RescueGuanoLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/RescueGuano/DistractGuard.h"
#include "Scenes/Platformer/Quests/EndianForest/RescueGuano/RescueGuano.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TownExitBlocked.h"

using namespace cocos2d;

const std::string RescueGuanoLine::MapKeyQuestLine = "rescue-guano";

RescueGuanoLine* RescueGuanoLine::create()
{
	RescueGuanoLine* instance = new RescueGuanoLine();

	instance->autorelease();

	return instance;
}

RescueGuanoLine::RescueGuanoLine() : super(RescueGuanoLine::MapKeyQuestLine, {
	QuestData(DistractGuard::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return DistractGuard::create(owner, questLine, questTag); }),
	QuestData(RescueGuano::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return RescueGuano::create(owner, questLine, questTag); }),
})
{
}

RescueGuanoLine::~RescueGuanoLine()
{
}
