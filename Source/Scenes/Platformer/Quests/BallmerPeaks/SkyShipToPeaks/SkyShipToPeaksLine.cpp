#include "SkyShipToPeaksLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/BallmerPeaks/SkyShipToPeaks/IrmikRescued.h"
#include "Scenes/Platformer/Quests/BallmerPeaks/SkyShipToPeaks/RescueIrmik.h"

using namespace cocos2d;

const std::string SkyShipToPeaksLine::MapKeyQuestLine = "sky-ship-to-peaks";

SkyShipToPeaksLine* SkyShipToPeaksLine::create()
{
	SkyShipToPeaksLine* instance = new SkyShipToPeaksLine();

	instance->autorelease();

	return instance;
}

SkyShipToPeaksLine::SkyShipToPeaksLine() : super(SkyShipToPeaksLine::MapKeyQuestLine,
	{
		QuestData(RescueIrmik::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return RescueIrmik::create(owner, questLine); }),
		QuestData(IrmikRescued::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return IrmikRescued::create(owner, questLine); }),
	})
{
}

SkyShipToPeaksLine::~SkyShipToPeaksLine()
{
}

QuestLine* SkyShipToPeaksLine::clone()
{
	return SkyShipToPeaksLine::create();
}
