#include "HackableAttribute.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Hackables/Clippy.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

HackableAttribute::HackableAttribute(int requiredHackFlag, float duration, float cooldown, std::string iconResource, LocalizedString* name, HackablePreview* hackablePreview, Clippy* clippy)
{
	this->requiredHackFlag = requiredHackFlag;
	this->duration = duration;
	this->cooldown = cooldown;
	this->iconResource = iconResource;
	this->name = name;
	this->hackablePreview = hackablePreview;
	this->elapsedDuration = this->duration;
	this->elapsedCooldown = this->cooldown;
	this->clippy = clippy == nullptr ? nullptr : clippy->refClone();
	this->isTimerPaused = false;

	if (this->hackablePreview != nullptr)
	{
		this->hackablePreview->retain();
	}

	if (this->clippy != nullptr)
	{
		this->clippy->retain();
	}

	if (this->name != nullptr)
	{
		this->addChild(this->name); // Retain with event listening
	}
}

HackableAttribute::~HackableAttribute()
{
	if (this->hackablePreview != nullptr)
	{
		this->hackablePreview->release();
	}

	if (this->clippy != nullptr)
	{
		this->clippy->release();
	}
}

void HackableAttribute::onEnter()
{
	super::onEnter();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		this->restoreState();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventPauseHackTimers, [=](EventCustom* eventCustom)
	{
		this->isTimerPaused = true;
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventResumeHackTimers, [=](EventCustom* eventCustom)
	{
		this->isTimerPaused = false;
	}));

	this->scheduleUpdate();
}

void HackableAttribute::update(float dt)
{
	super::update(dt);

	if (this->isTimerPaused)
	{
		return;
	}

	if (this->elapsedDuration < this->duration)
	{
		this->elapsedDuration += dt;

		if (this->elapsedDuration >= this->duration)
		{
			this->restoreState();
		}
	}

	if (this->elapsedCooldown < this->cooldown)
	{
		this->elapsedCooldown += dt;
	}
}

void HackableAttribute::resetTimer()
{
	this->elapsedDuration = 0.0f;
	this->elapsedCooldown = 0.0f;
}

void HackableAttribute::restoreState()
{
}

void* HackableAttribute::getPointer()
{
	return nullptr;
}

int HackableAttribute::getRequiredHackFlag()
{
	return this->requiredHackFlag;
}

float HackableAttribute::getElapsedDuration()
{
	return this->elapsedDuration;
}

float HackableAttribute::getDuration()
{
	return this->duration;
}

bool HackableAttribute::isCooldownComplete()
{
	return this->elapsedCooldown >= this->cooldown;
}

float HackableAttribute::getElapsedCooldown()
{
	return this->elapsedCooldown;
}

float HackableAttribute::getCooldown()
{
	return this->cooldown;
}

std::string HackableAttribute::getIconResource()
{
	return this->iconResource;
}

LocalizedString* HackableAttribute::getName()
{
	return this->name;
}

HackablePreview* HackableAttribute::getHackablePreview()
{
	return this->hackablePreview;
}

Clippy* HackableAttribute::getClippy()
{
	return this->clippy;
}
