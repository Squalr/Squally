#include "HackableBase.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Localization/LocalizedString.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

bool HackableBase::HackTimersPaused = false;

HackableBase::HackableBase(
	std::string hackableIdentifier,
	int requiredHackFlag,
	float duration,
	float cooldown,
	HackBarColor hackBarColor,
	std::string iconResource,
	LocalizedString* name,
	HackablePreview* hackablePreview)
{
	this->hackableIdentifier = hackableIdentifier;
	this->requiredHackFlag = requiredHackFlag;
	this->hackBarColor = hackBarColor;
	this->iconResource = iconResource;
	this->name = name;
	this->hackablePreview = hackablePreview;
	this->duration = duration;
	this->cooldown = cooldown;
	this->elapsedDuration = duration;
	this->elapsedCooldown = cooldown;

	if (this->hackablePreview != nullptr)
	{
		this->hackablePreview->retain();
	}

	if (this->name != nullptr)
	{
		this->addChild(this->name); // Retain with event listening
	}
}

HackableBase::~HackableBase()
{
	if (this->hackablePreview != nullptr)
	{
		this->hackablePreview->release();
	}
}

void HackableBase::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void HackableBase::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackRestoreStatePrefix + this->getHackableIdentifier(), [=](EventCustom* eventCustom)
	{
		HackableEvents::HackRestoreStateArgs* args = static_cast<HackableEvents::HackRestoreStateArgs*>(eventCustom->getUserData());

		// Only allow one hackable attribute to restore the state to prevent duplicate wasted work.
		if (args != nullptr && !args->isHandled())
		{
			args->handle();

			this->restoreState();
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventQueryAttributeCountPrefix + this->getHackableIdentifier(), [=](EventCustom* eventCustom)
	{
		HackableEvents::HackableBaseQueryArgs* args = static_cast<HackableEvents::HackableBaseQueryArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			args->count++;
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		this->restoreState();
		this->resetTimer();
	}));
}

void HackableBase::update(float dt)
{
	super::update(dt);

	if (HackableBase::HackTimersPaused)
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

std::string HackableBase::getHackableIdentifier()
{
	return this->hackableIdentifier;
}

void* HackableBase::getPointer()
{
	return nullptr;
}

int HackableBase::getRequiredHackFlag()
{
	return this->requiredHackFlag;
}

float HackableBase::getElapsedDuration()
{
	return this->elapsedDuration;
}

float HackableBase::getDuration()
{
	return this->duration;
}

bool HackableBase::isComplete()
{
	return this->getElapsedDuration() >= this->getDuration();
}

bool HackableBase::isCooldownComplete()
{
	return this->getElapsedCooldown() >= this->getCooldown();
}

float HackableBase::getElapsedCooldown()
{
	return this->elapsedCooldown;
}

float HackableBase::getCooldown()
{
	return this->cooldown;
}

std::string HackableBase::getHackBarResource()
{
	switch(this->getHackBarColor())
	{
		case HackableBase::HackBarColor::Blue:
		{
			return UIResources::HUD_FillBlue;
		}
		case HackableBase::HackBarColor::Gray:
		{
			return UIResources::HUD_FillGray;
		}
		case HackableBase::HackBarColor::Green:
		{
			return UIResources::HUD_FillGreen;
		}
		case HackableBase::HackBarColor::Orange:
		{
			return UIResources::HUD_FillOrange;
		}
		case HackableBase::HackBarColor::Pink:
		{
			return UIResources::HUD_FillPink;
		}
		case HackableBase::HackBarColor::Red:
		{
			return UIResources::HUD_FillRed;
		}
		case HackableBase::HackBarColor::Teal:
		{
			return UIResources::HUD_FillTeal;
		}
		case HackableBase::HackBarColor::Yellow:
		{
			return UIResources::HUD_FillYellow;
		}
		default:
		case HackableBase::HackBarColor::Purple:
		{
			return UIResources::HUD_FillPurple;
		}
	}
}

HackableBase::HackBarColor HackableBase::getHackBarColor()
{
	return this->hackBarColor;
}

std::string HackableBase::getIconResource()
{
	return this->iconResource;
}

LocalizedString* HackableBase::getName()
{
	return this->name;
}

HackablePreview* HackableBase::getHackablePreview()
{
	return this->hackablePreview;
}

void HackableBase::restoreState()
{
}

void HackableBase::restoreStateIfUnique()
{
	// Some example scenarios of why this is needed:
	// 1) A buff with a hackable is removed, and this was the only hackable (ie only 1 buff, 1 hackable code). Restore the state.
	// 2) A buff with a hackable is removed, but another mob has the same buff, thus we should be waiting on the duration before restoring the state.

	HackableEvents::HackableBaseQueryArgs queryArgs = HackableEvents::HackableBaseQueryArgs(this->getHackableIdentifier());

	HackableEvents::TriggerQueryAttributeCount(&queryArgs);
	
	if (queryArgs.count <= 1)
	{
		this->restoreState();
	}
}

void HackableBase::startTimer()
{
	this->elapsedDuration = 0.0f;
	this->elapsedCooldown = 0.0f;
}

void HackableBase::resetTimer()
{
	this->elapsedDuration = this->duration;
	this->elapsedCooldown = this->cooldown;
}
