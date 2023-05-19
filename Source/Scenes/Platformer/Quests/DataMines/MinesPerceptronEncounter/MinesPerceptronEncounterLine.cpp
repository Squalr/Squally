#include "MinesPerceptronEncounterLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/DataMines/MinesPerceptronEncounter/MinesPerceptronEncounter.h"

using namespace cocos2d;

const std::string MinesPerceptronEncounterLine::MapKeyQuestLine = "mines-perceptron-encounter";

MinesPerceptronEncounterLine* MinesPerceptronEncounterLine::create()
{
	MinesPerceptronEncounterLine* instance = new MinesPerceptronEncounterLine();

	instance->autorelease();

	return instance;
}

MinesPerceptronEncounterLine::MinesPerceptronEncounterLine() : super(MinesPerceptronEncounterLine::MapKeyQuestLine,
	{
		QuestData(MinesPerceptronEncounter::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return MinesPerceptronEncounter::create(owner, questLine); }),
	})
{
}

MinesPerceptronEncounterLine::~MinesPerceptronEncounterLine()
{
}

QuestLine* MinesPerceptronEncounterLine::clone()
{
	return MinesPerceptronEncounterLine::create();
}
