#include "MagesWarpLockLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/MagesWarpLock/MagesWarpLock.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/FindElrielLine.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TalkToElriel.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/WindSpellbook.h"

using namespace cocos2d;

const std::string MagesWarpLockLine::MapKeyQuestLine = "mages-warp-lock";

MagesWarpLockLine* MagesWarpLockLine::create()
{
	MagesWarpLockLine* instance = new MagesWarpLockLine();

	instance->autorelease();

	return instance;
}

MagesWarpLockLine::MagesWarpLockLine() : super(MagesWarpLockLine::MapKeyQuestLine,
	{
		QuestData(MagesWarpLock::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return MagesWarpLock::create(owner, questLine); }),
	},
	(QuestLine*)FindElrielLine::create(), WindSpellbook::MapKeyQuest)
{
}

MagesWarpLockLine::~MagesWarpLockLine()
{
}

QuestLine* MagesWarpLockLine::clone()
{
	return MagesWarpLockLine::create();
}
