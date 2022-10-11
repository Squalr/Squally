#include "SkyShipToTempleLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/FindElrielLine.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TalkToElriel.h"
#include "Scenes/Platformer/Quests/EndianForest/SkyShipToTemple/SkyShipUnlocked.h"

using namespace cocos2d;

const std::string SkyShipToTempleLine::MapKeyQuestLine = "sky-ship-to-temple";

SkyShipToTempleLine* SkyShipToTempleLine::create()
{
	SkyShipToTempleLine* instance = new SkyShipToTempleLine();

	instance->autorelease();

	return instance;
}

SkyShipToTempleLine::SkyShipToTempleLine() : super(SkyShipToTempleLine::MapKeyQuestLine,
	{
		QuestData(SkyShipUnlocked::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return SkyShipUnlocked::create(owner, questLine); }),
	},
	(QuestLine*)FindElrielLine::create(), TalkToElriel::MapKeyQuest)
{
}

SkyShipToTempleLine::~SkyShipToTempleLine()
{
}

QuestLine* SkyShipToTempleLine::clone()
{
	return SkyShipToTempleLine::create();
}
