#include "FirstIOULine.h"

#include "cocos/base/CCValue.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/IOU/FirstIOUFound.h"

using namespace cocos2d;

const std::string FirstIOULine::MapKeyQuestLine = "first-iou";
const std::map<std::string, std::tuple<bool, std::function<QuestTask*(GameObject*, std::string, std::string)>>> FirstIOULine::Quests =
{
	{ FirstIOUFound::MapKeyQuest, { true, [](GameObject* owner, std::string questLine, std::string questTag) { return FirstIOUFound::create(owner, questLine, questTag); }}},
};

FirstIOULine* FirstIOULine::create()
{
	FirstIOULine* instance = new FirstIOULine();

	instance->autorelease();

	return instance;
}

QuestTask* FirstIOULine::deserialize(GameObject* owner, std::string questTask, std::string questTag)
{
	if (FirstIOULine::Quests.find(questTask) != FirstIOULine::Quests.end())
	{
		return std::get<1>(FirstIOULine::Quests.at(questTask))(owner, FirstIOULine::MapKeyQuestLine, questTag);
	}

	return nullptr;
}
