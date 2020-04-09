#include "SailForRuinsLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/SailForRuins/SailForRuins.h"
#include "Scenes/Platformer/Quests/EndianForest/SaveTown/SaveTownLine.h"

using namespace cocos2d;

const std::string SailForRuinsLine::MapKeyQuestLine = "sail-for-ruins";

SailForRuinsLine* SailForRuinsLine::create()
{
	SailForRuinsLine* instance = new SailForRuinsLine();

	instance->autorelease();

	return instance;
}

SailForRuinsLine::SailForRuinsLine() : super(SailForRuinsLine::MapKeyQuestLine,
	{
		QuestData(SailForRuins::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return SailForRuins::create(owner, questLine); }),
	},
	(QuestLine*)SaveTownLine::create())
{
}

SailForRuinsLine::~SailForRuinsLine()
{
}

QuestLine* SailForRuinsLine::clone()
{
	return SailForRuinsLine::create();
}
