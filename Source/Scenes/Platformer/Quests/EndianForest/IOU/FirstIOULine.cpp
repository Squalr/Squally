#include "FirstIOULine.h"

#include "cocos/base/CCValue.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/IOU/FirstIOUFound.h"

using namespace cocos2d;

const std::string FirstIOULine::MapKeyQuestLine = "first-iou";

FirstIOULine* FirstIOULine::create()
{
	FirstIOULine* instance = new FirstIOULine();

	instance->autorelease();

	return instance;
}

FirstIOULine::FirstIOULine() : super(FirstIOULine::MapKeyQuestLine, {
	QuestData(FirstIOUFound::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return FirstIOUFound::create(owner, questLine, questTag); }),
})
{
}

FirstIOULine::~FirstIOULine()
{
}
