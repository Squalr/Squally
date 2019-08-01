#include "IntroLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/MeetFlyBot.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/HelpSquallyHeal.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/SpotOrcGrunt.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/TeachHackerMode.h"

using namespace cocos2d;

const std::string IntroLine::MapKeyQuestLine = "intro";

GameObject* IntroLine::deserialize(GameObject* owner, std::string questLine, std::string questTask, std::string questTag)
{
	static const std::map<std::string, std::function<GameObject*(GameObject*, std::string, std::string)>> Quests =
	{
		{ MeetFlyBot::MapKeyQuest, [=](GameObject* owner, std::string questLine, std::string questTag) { return MeetFlyBot::create(owner, questLine, questTag); }},
		{ HelpSquallyHeal::MapKeyQuest, [=](GameObject* owner, std::string questLine, std::string questTag) { return HelpSquallyHeal::create(owner, questLine, questTag); }},
		{ TeachHackerMode::MapKeyQuest, [=](GameObject* owner, std::string questLine, std::string questTag) { return TeachHackerMode::create(owner, questLine, questTag); }},
		{ SpotOrcGrunt::MapKeyQuest, [=](GameObject* owner, std::string questLine, std::string questTag) { return SpotOrcGrunt::create(owner, questLine, questTag); }},
	};

	if (Quests.find(questTask) != Quests.end())
	{
		return Quests.at(questTask)(owner, questLine, questTag);
	}

	return nullptr;
}
