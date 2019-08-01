#include "DeveloperLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/Developer/Task1.h"
#include "Scenes/Platformer/Quests/EndianForest/Developer/Task2.h"
#include "Scenes/Platformer/Quests/EndianForest/Developer/Task3.h"
#include "Scenes/Platformer/Quests/EndianForest/Developer/Task4.h"

using namespace cocos2d;

const std::string DeveloperLine::MapKeyQuestLine = "intro";

GameObject* DeveloperLine::deserialize(GameObject* owner, std::string questLine, std::string questTask, std::string questTag)
{
	static const std::map<std::string, std::function<GameObject*(GameObject*, std::string, std::string)>> Quests =
	{
		{ Task1::MapKeyQuest, [=](GameObject* owner, std::string questLine, std::string questTag) { return Task1::create(owner, questLine, questTag); }},
		{ Task2::MapKeyQuest, [=](GameObject* owner, std::string questLine, std::string questTag) { return Task2::create(owner, questLine, questTag); }},
		{ Task3::MapKeyQuest, [=](GameObject* owner, std::string questLine, std::string questTag) { return Task3::create(owner, questLine, questTag); }},
		{ Task4::MapKeyQuest, [=](GameObject* owner, std::string questLine, std::string questTag) { return Task4::create(owner, questLine, questTag); }},
	};

	if (Quests.find(questTask) != Quests.end())
	{
		return Quests.at(questTask)(owner, questLine, questTag);
	}

	return nullptr;
}
