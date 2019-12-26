#include "WindBlessingLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/FindElrielLine.h"
#include "Scenes/Platformer/Quests/EndianForest/WindBlessing/WindBlessing.h"

using namespace cocos2d;

const std::string WindBlessingLine::MapKeyQuestLine = "wind-blessing";

WindBlessingLine* WindBlessingLine::create()
{
	WindBlessingLine* instance = new WindBlessingLine();

	instance->autorelease();

	return instance;
}

WindBlessingLine::WindBlessingLine() : super(WindBlessingLine::MapKeyQuestLine,
	{
		QuestData(WindBlessing::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return WindBlessing::create(owner, questLine); }),
	},
	(QuestLine*)FindElrielLine::create())
{
}

WindBlessingLine::~WindBlessingLine()
{
}

QuestLine* WindBlessingLine::clone()
{
	return WindBlessingLine::create();
}
