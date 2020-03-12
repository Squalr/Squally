#include "IntroLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/MeetScrappy.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/SpotOrcGrunt.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/SpotTrainingDummy.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/TeachHackerMode.h"

using namespace cocos2d;

const std::string IntroLine::MapKeyQuestLine = "intro";

IntroLine* IntroLine::create()
{
	IntroLine* instance = new IntroLine();

	instance->autorelease();

	return instance;
}

IntroLine::IntroLine() : super(IntroLine::MapKeyQuestLine, {
	QuestData(MeetScrappy::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine) { return MeetScrappy::create(owner, questLine); }),
	QuestData(TeachHackerMode::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine) { return TeachHackerMode::create(owner, questLine); }),
	QuestData(SpotTrainingDummy::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine) { return SpotTrainingDummy::create(owner, questLine); }),
	QuestData(SpotOrcGrunt::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine) { return SpotOrcGrunt::create(owner, questLine); }),
})
{
}

IntroLine::~IntroLine()
{
}

QuestLine* IntroLine::clone()
{
	return IntroLine::create();
}
