#include "Buff.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Entities/Platformer/PlatformerEntity.h"

using namespace cocos2d;

const float Buff::DURATION_INFINITE = 0.0f;

Buff::Buff(PlatformerEntity* target, std::string iconResource, int stacks, float tickDuration, float duration)
{
	this->target = target;
	this->stacks = stacks;
	this->tickDuration = tickDuration;
	this->duration = duration;
	this->iconFrame = Sprite::create(iconResource);
	this->icon = Sprite::create(iconResource);
	this->hackables = std::vector<HackableCode*>();

	this->addChild(this->iconFrame);
	this->addChild(this->icon);
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
	for (auto it = this->hackables.begin(); it != this->hackables.end(); it++)
	{
		this->target->unregisterCode(*it);
	}
}

void Buff::tick()
{
}
