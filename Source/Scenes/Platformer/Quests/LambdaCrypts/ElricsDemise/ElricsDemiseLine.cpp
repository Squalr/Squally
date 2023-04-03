#include "ElricsDemiseLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/ElricsDemise/TalkToAmelia.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/ElricsDemise/ElricsDemise.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/ElricsDemise/ElricsPlea.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/ElricsDemise/DefeatElric.h"

using namespace cocos2d;

const std::string ElricsDemiseLine::MapKeyQuestLine = "elrics-demise";

ElricsDemiseLine* ElricsDemiseLine::create()
{
	ElricsDemiseLine* instance = new ElricsDemiseLine();

	instance->autorelease();

	return instance;
}

ElricsDemiseLine::ElricsDemiseLine() : super(ElricsDemiseLine::MapKeyQuestLine,
	{
		QuestData(ElricsPlea::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return ElricsPlea::create(owner, questLine); }),
		QuestData(TalkToAmelia::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return TalkToAmelia::create(owner, questLine); }),
		QuestData(ElricsDemise::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return ElricsDemise::create(owner, questLine); }),
		QuestData(DefeatElric::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return DefeatElric::create(owner, questLine); }),
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
