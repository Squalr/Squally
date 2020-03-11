#include "LianaDoorLocked.h"

#include "Objects/Platformer/Interactables/Doors/Portal.h"

using namespace cocos2d;

const std::string LianaDoorLocked::MapKeyQuest = "liana-door-locked";

LianaDoorLocked* LianaDoorLocked::create(GameObject* owner, QuestLine* questLine)
{
	LianaDoorLocked* instance = new LianaDoorLocked(owner, questLine);

	instance->autorelease();

	return instance;
}

LianaDoorLocked::LianaDoorLocked(GameObject* owner, QuestLine* questLine) : super(owner, questLine, LianaDoorLocked::MapKeyQuest, false)
{
	this->portal = static_cast<Portal*>(owner);

	if (this->portal != nullptr)
	{
		this->portal->lock(false);
	}
}

LianaDoorLocked::~LianaDoorLocked()
{
}

void LianaDoorLocked::onLoad(QuestState questState)
{
	if (this->portal != nullptr)
	{
		switch(questState)
		{
			case QuestState::Complete:
			{
				this->portal->unlock(false);
				break;
			}
			case QuestState::Active:
			case QuestState::ActiveThroughSkippable:
			default:
			{
				break;
			}
		}
	}
}

void LianaDoorLocked::onActivate(bool isActiveThroughSkippable)
{
}

void LianaDoorLocked::onComplete()
{
}

void LianaDoorLocked::onSkipped()
{
}
