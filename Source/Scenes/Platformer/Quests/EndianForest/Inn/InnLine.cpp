#include "InnLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/FindElrielLine.h"
#include "Scenes/Platformer/Quests/EndianForest/Inn/EnterInn.h"

using namespace cocos2d;

const std::string InnLine::MapKeyQuestLine = "inn";

InnLine* InnLine::create()
{
	InnLine* instance = new InnLine();

	instance->autorelease();

	return instance;
}

InnLine::InnLine() : super(InnLine::MapKeyQuestLine,
	{
		QuestData(EnterInn::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return EnterInn::create(owner, questLine, questTag); }),
	},
	(QuestLine*)FindElrielLine::create())
{
}

InnLine::~InnLine()
{
}
