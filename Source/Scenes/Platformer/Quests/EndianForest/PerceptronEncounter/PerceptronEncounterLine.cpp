#include "PerceptronEncounterLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/PerceptronEncounter/PerceptronEncounter.h"

using namespace cocos2d;

const std::string PerceptronEncounterLine::MapKeyQuestLine = "perceptron-encounter";

PerceptronEncounterLine* PerceptronEncounterLine::create()
{
	PerceptronEncounterLine* instance = new PerceptronEncounterLine();

	instance->autorelease();

	return instance;
}

PerceptronEncounterLine::PerceptronEncounterLine() : super(PerceptronEncounterLine::MapKeyQuestLine,
	{
		QuestData(PerceptronEncounter::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return PerceptronEncounter::create(owner, questLine); }),
	})
{
}

PerceptronEncounterLine::~PerceptronEncounterLine()
{
}

QuestLine* PerceptronEncounterLine::clone()
{
	return PerceptronEncounterLine::create();
}
