#include "SkyShipToCastleLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/CastleValgrind/SkyShipToCastle/FinchRescued.h"

using namespace cocos2d;

const std::string SkyShipToCastleLine::MapKeyQuestLine = "sky-ship-to-castle";

SkyShipToCastleLine* SkyShipToCastleLine::create()
{
	SkyShipToCastleLine* instance = new SkyShipToCastleLine();

	instance->autorelease();

	return instance;
}

SkyShipToCastleLine::SkyShipToCastleLine() : super(SkyShipToCastleLine::MapKeyQuestLine,
	{
		QuestData(FinchRescued::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return FinchRescued::create(owner, questLine); }),
	}/*, (QuestLine*)FindElrielLine::create(), TalkToElriel::MapKeyQuest*/)
{
}

SkyShipToCastleLine::~SkyShipToCastleLine()
{
}

QuestLine* SkyShipToCastleLine::clone()
{
	return SkyShipToCastleLine::create();
}
