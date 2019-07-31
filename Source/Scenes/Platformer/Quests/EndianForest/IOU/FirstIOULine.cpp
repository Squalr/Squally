#include "FirstIOULine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/IOU/FirstIOUFound.h"

using namespace cocos2d;

const std::string FirstIOULine::MapKeyQuestLine = "first-iou";

FirstIOULine* FirstIOULine::create(std::string quest, std::string questTag, GameObject* owner)
{
	FirstIOULine* instance = new FirstIOULine(quest, questTag, owner);
	
	instance->autorelease();

	return instance;
}

FirstIOULine::FirstIOULine(std::string quest, std::string questTag, GameObject* owner) : super(
	FirstIOULine::MapKeyQuestLine,
	quest,
	questTag,
	{
		(QuestTask*)FirstIOUFound::create(quest == FirstIOUFound::MapKeyQuest ? owner : nullptr, FirstIOULine::MapKeyQuestLine),
	})
{
}

FirstIOULine::~FirstIOULine()
{
}

void FirstIOULine::initializePositions()
{
	super::initializePositions();
}

void FirstIOULine::initializeListeners()
{
	super::initializeListeners();
}
