#include "DeveloperLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/Developer/Task1.h"
#include "Scenes/Platformer/Quests/EndianForest/Developer/Task2.h"
#include "Scenes/Platformer/Quests/EndianForest/Developer/Task3.h"
#include "Scenes/Platformer/Quests/EndianForest/Developer/Task4.h"

using namespace cocos2d;

const std::string DeveloperLine::MapKeyQuestLine = "intro";
const std::map<std::string, std::tuple<bool, std::function<QuestTask*(GameObject*, std::string, std::string)>>> DeveloperLine::Quests =
{
	{ Task1::MapKeyQuest, { true, [](GameObject* owner, std::string questLine, std::string questTag) { return Task1::create(owner, questLine, questTag); }}},
	{ Task2::MapKeyQuest, { true, [](GameObject* owner, std::string questLine, std::string questTag) { return Task2::create(owner, questLine, questTag); }}},
	{ Task3::MapKeyQuest, { true, [](GameObject* owner, std::string questLine, std::string questTag) { return Task3::create(owner, questLine, questTag); }}},
	{ Task4::MapKeyQuest, { true, [](GameObject* owner, std::string questLine, std::string questTag) { return Task4::create(owner, questLine, questTag); }}},
};

DeveloperLine* DeveloperLine::create()
{
	DeveloperLine* instance = new DeveloperLine();

	instance->autorelease();

	return instance;
}

QuestTask* DeveloperLine::deserialize(GameObject* owner, std::string questTask, std::string questTag)
{
	if (DeveloperLine::Quests.find(questTask) != DeveloperLine::Quests.end())
	{
		return std::get<1>(DeveloperLine::Quests.at(questTask))(owner, DeveloperLine::MapKeyQuestLine, questTag);
	}

	return nullptr;
}
