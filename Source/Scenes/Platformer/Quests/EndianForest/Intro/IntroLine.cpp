#include "IntroLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/MeetFlyBot.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/HelpSquallyHeal.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/SpotOrcGrunt.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/TeachHackerMode.h"

using namespace cocos2d;

const std::string IntroLine::MapKeyQuestLine = "intro";
const std::map<std::string, std::tuple<bool, std::function<QuestTask*(GameObject*, QuestLine*, std::string)>>> IntroLine::Quests =
{
	{ MeetFlyBot::MapKeyQuest, { true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return MeetFlyBot::create(owner, questLine, questTag); }}},
	{ HelpSquallyHeal::MapKeyQuest, { true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return HelpSquallyHeal::create(owner, questLine, questTag); }}},
	{ TeachHackerMode::MapKeyQuest, { true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return TeachHackerMode::create(owner, questLine, questTag); }}},
	{ SpotOrcGrunt::MapKeyQuest, { true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return SpotOrcGrunt::create(owner, questLine, questTag); }}},
};

IntroLine* IntroLine::create()
{
	IntroLine* instance = new IntroLine();

	instance->autorelease();

	return instance;
}

IntroLine::IntroLine() : super(IntroLine::MapKeyQuestLine, IntroLine::Quests)
{
}

IntroLine::~IntroLine()
{
}
