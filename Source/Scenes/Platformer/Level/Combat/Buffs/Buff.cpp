#include "Buff.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Entities/Platformer/PlatformerEntity.h"

using namespace cocos2d;

Buff::Buff(PlatformerEntity* target)
{
	this->target = target;
	this->hackables = std::vector<HackableCode*>();
}

Buff::~Buff()
{
}

void Buff::onEnter()
{
	super::onEnter();

	this->registerHackables();
}

void Buff::registerHackables()
{
}

void Buff::unregisterHackables()
{
	if (this->target == nullptr)
	{
		return;
	}

	for (auto it = this->hackables.begin(); it != this->hackables.end(); it++)
	{
		this->target->unregisterCode(*it);
	}
}

void Buff::removeBuff()
{
	this->unregisterHackables();

	if (this->getParent() != nullptr)
	{
		this->getParent()->removeChild(this);
	}
}
