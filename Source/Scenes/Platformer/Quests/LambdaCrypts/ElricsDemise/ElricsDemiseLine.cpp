#include "ElricsDemiseLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/ElricsDemise/TalkToAmelia.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/ElricsDemise/ElricsDemise.h"

using namespace cocos2d;

const std::string ElricsDemiseLine::MapKeyQuestLine = "craft-hell-gate-crystal";

ElricsDemiseLine* ElricsDemiseLine::create()
{
	ElricsDemiseLine* instance = new ElricsDemiseLine();

	instance->autorelease();

	return instance;
}

ElricsDemiseLine::ElricsDemiseLine() : super(ElricsDemiseLine::MapKeyQuestLine,
	{
		QuestData(TalkToAmelia::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return TalkToAmelia::create(owner, questLine); }),
		QuestData(ElricsDemise::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return ElricsDemise::create(owner, questLine); }),
	})
{
}

ElricsDemiseLine::~ElricsDemiseLine()
{
}

QuestLine* ElricsDemiseLine::clone()
{
	return ElricsDemiseLine::create();
}
