#include "PerceptronFightLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/VoidStar/PerceptronFight/PerceptronDeath.h"
#include "Scenes/Platformer/Quests/VoidStar/PerceptronFight/PerceptronEscape.h"
#include "Scenes/Platformer/Quests/VoidStar/PerceptronFight/PerceptronFight.h"
#include "Scenes/Platformer/Quests/VoidStar/PerceptronFight/PerceptronFinale.h"

using namespace cocos2d;

const std::string PerceptronFightLine::MapKeyQuestLine = "perceptron-fight";

PerceptronFightLine* PerceptronFightLine::create()
{
	PerceptronFightLine* instance = new PerceptronFightLine();

	instance->autorelease();

	return instance;
}

PerceptronFightLine::PerceptronFightLine() : super(PerceptronFightLine::MapKeyQuestLine,
	{
		QuestData(PerceptronFight::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return PerceptronFight::create(owner, questLine); }),
		QuestData(PerceptronEscape::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return PerceptronEscape::create(owner, questLine); }),
		QuestData(PerceptronFinale::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return PerceptronFinale::create(owner, questLine); }),
		QuestData(PerceptronDeath::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return PerceptronDeath::create(owner, questLine); }),
	})
{
}

PerceptronFightLine::~PerceptronFightLine()
{
}

QuestLine* PerceptronFightLine::clone()
{
	return PerceptronFightLine::create();
}
