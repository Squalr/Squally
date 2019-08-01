#include "IntroLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/MeetFlyBot.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/HelpSquallyHeal.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/SpotOrcGrunt.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/TeachHackerMode.h"

using namespace cocos2d;

const std::string IntroLine::MapKeyQuestLine = "intro";
const std::map<std::string, std::tuple<bool, std::function<QuestTask*(GameObject*, std::string, std::string)>>> IntroLine::Quests =
{
	{ MeetFlyBot::MapKeyQuest, { true, [](GameObject* owner, std::string questLine, std::string questTag) { return MeetFlyBot::create(owner, questLine, questTag); }}},
	{ HelpSquallyHeal::MapKeyQuest, { true, [](GameObject* owner, std::string questLine, std::string questTag) { return HelpSquallyHeal::create(owner, questLine, questTag); }}},
	{ TeachHackerMode::MapKeyQuest, { true, [](GameObject* owner, std::string questLine, std::string questTag) { return TeachHackerMode::create(owner, questLine, questTag); }}},
	{ SpotOrcGrunt::MapKeyQuest, { true, [](GameObject* owner, std::string questLine, std::string questTag) { return SpotOrcGrunt::create(owner, questLine, questTag); }}},
};

IntroLine* IntroLine::create()
{
	IntroLine* instance = new IntroLine();

	instance->autorelease();

	return instance;
}

IntroLine::IntroLine()
{
}

IntroLine::~IntroLine()
{
}

QuestTask* IntroLine::deserialize(GameObject* owner, std::string questTask, std::string questTag)
{
	if (IntroLine::Quests.find(questTask) != IntroLine::Quests.end())
	{
		return std::get<1>(IntroLine::Quests.at(questTask))(owner, IntroLine::MapKeyQuestLine, questTag);
	}

	return nullptr;
}
