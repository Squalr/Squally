#include "MeetFlyBot.h"

#include "cocos/base/CCValue.h"

#include "Engine/Events/QuestEvents.h"

using namespace cocos2d;

const std::string MeetFlyBot::MapKeyQuest = "meet-flybot";

MeetFlyBot* MeetFlyBot::create()
{
	MeetFlyBot* instance = new MeetFlyBot();

	instance->autorelease();

	return instance;
}

MeetFlyBot::MeetFlyBot() : super(MeetFlyBot::MapKeyQuest)
{
}

MeetFlyBot::~MeetFlyBot()
{
}

void MeetFlyBot::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent(MeetFlyBot::MapKeyQuest, [=](ValueMap args)
	{
		QuestEvents::TriggerAdvanceToNextQuest(QuestEvents::AdvanceNextQuestArgs(this));
	});
}
