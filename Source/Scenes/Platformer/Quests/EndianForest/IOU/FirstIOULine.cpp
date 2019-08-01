#include "FirstIOULine.h"

#include "cocos/base/CCValue.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/IOU/FirstIOUFound.h"

using namespace cocos2d;

const std::string FirstIOULine::MapKeyQuestLine = "first-iou";

GameObject* FirstIOULine::deserialize(GameObject* owner, std::string questLine, std::string questTask, std::string questTag)
{
	static const std::map<std::string, std::function<GameObject*(GameObject*, std::string, std::string)>> Quests =
	{
		{ FirstIOUFound::MapKeyQuest, [=](GameObject* owner, std::string questLine, std::string questTag) { return FirstIOUFound::create(owner, questLine, questTag); }},
	};

	if (Quests.find(questTask) != Quests.end())
	{
		return Quests.at(questTask)(owner, questLine, questTag);
	}

	return nullptr;
}
