#include "DiscoverCharterShip.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DiscoverCharterShip::MapKeyQuest = "discover-charter-ship";

DiscoverCharterShip* DiscoverCharterShip::create(GameObject* owner, QuestLine* questLine)
{
	DiscoverCharterShip* instance = new DiscoverCharterShip(owner, questLine);

	instance->autorelease();

	return instance;
}

DiscoverCharterShip::DiscoverCharterShip(GameObject* owner, QuestLine* questLine) : super(owner, questLine, DiscoverCharterShip::MapKeyQuest, false)
{
}

DiscoverCharterShip::~DiscoverCharterShip()
{
}

void DiscoverCharterShip::onLoad(QuestState questState)
{
	this->complete();
}

void DiscoverCharterShip::onActivate(bool isActiveThroughSkippable)
{
}

void DiscoverCharterShip::onComplete()
{
}

void DiscoverCharterShip::onSkipped()
{
}
