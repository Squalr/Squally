#include "IntroLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/MeetFlyBot.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/HelpSquallyHeal.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/SpotOrcGrunt.h"
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
	QuestData(MeetFlyBot::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return MeetFlyBot::create(owner, questLine, questTag); }),
	QuestData(HelpSquallyHeal::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return HelpSquallyHeal::create(owner, questLine, questTag); }),
	QuestData(TeachHackerMode::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return TeachHackerMode::create(owner, questLine, questTag); }),
	QuestData(SpotOrcGrunt::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return SpotOrcGrunt::create(owner, questLine, questTag); }),
})
{
}

IntroLine::~IntroLine()
{
}
