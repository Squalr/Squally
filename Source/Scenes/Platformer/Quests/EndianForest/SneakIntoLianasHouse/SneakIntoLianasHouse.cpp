#include "SneakIntoLianasHouse.h"

#include "Objects/Platformer/Interactables/Doors/Portal.h"

using namespace cocos2d;

const std::string SneakIntoLianasHouse::MapKeyQuest = "sneak-liana";

SneakIntoLianasHouse* SneakIntoLianasHouse::create(GameObject* owner, QuestLine* questLine)
{
	SneakIntoLianasHouse* instance = new SneakIntoLianasHouse(owner, questLine);

	instance->autorelease();

	return instance;
}

SneakIntoLianasHouse::SneakIntoLianasHouse(GameObject* owner, QuestLine* questLine) : super(owner, questLine, SneakIntoLianasHouse::MapKeyQuest, false)
{
	this->portal = static_cast<Portal*>(owner);
}

SneakIntoLianasHouse::~SneakIntoLianasHouse()
{
}

void SneakIntoLianasHouse::onLoad(QuestState questState)
{
	if (this->portal != nullptr)
	{
		this->portal->setOpenCallback([=]()
		{
			this->complete();

			return true;
		});
	}
}

void SneakIntoLianasHouse::onActivate(bool isActiveThroughSkippable)
{
}

void SneakIntoLianasHouse::onComplete()
{
}

void SneakIntoLianasHouse::onSkipped()
{
}
