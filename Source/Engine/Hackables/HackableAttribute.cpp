#include "HackableAttribute.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Hackables/Menus/Clippy.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Localization/LocalizedString.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

bool HackableAttribute::HackTimersPaused = false;
std::map<std::string, HackableAttribute::SharedState> HackableAttribute::SharedStateMap = std::map<std::string, HackableAttribute::SharedState>();

HackableAttribute::HackableAttribute(
	std::string hackableIdentifier,
	int requiredHackFlag,
	float duration,
	float cooldown,
	HackBarColor hackBarColor,
	std::string iconResource,
	LocalizedString* name,
	HackablePreview* hackablePreview,
	Clippy* clippy)
{
	this->hackableIdentifier = hackableIdentifier;
	this->requiredHackFlag = requiredHackFlag;
	this->hackBarColor = hackBarColor;
	this->iconResource = iconResource;
	this->name = name;
	this->hackablePreview = hackablePreview;
	this->clippy = clippy == nullptr ? nullptr : clippy->refClone();

	HackableAttribute::TryRegisterSharedState(this, SharedState(duration, cooldown));

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
}

void HackableAttribute::initializeListeners()
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
		HackableEvents::HackableAttributeQueryArgs* args = static_cast<HackableEvents::HackableAttributeQueryArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			args->count++;
		}
	}));
}

void HackableAttribute::UpdateSharedState(float dt)
{
	if (HackableAttribute::HackTimersPaused)
	{
		return;
	}

	for (auto next : HackableAttribute::SharedStateMap)
	{
		std::string key = next.first;

		if (HackableAttribute::SharedStateMap[key].elapsedDuration < HackableAttribute::SharedStateMap[key].duration)
		{
			HackableAttribute::SharedStateMap[key].elapsedDuration += dt;

			if (HackableAttribute::SharedStateMap[key].elapsedDuration >= HackableAttribute::SharedStateMap[key].duration)
			{
				HackableEvents::TriggerHackRestoreState(HackableEvents::HackRestoreStateArgs(key));
			}
		}

		if (HackableAttribute::SharedStateMap[key].elapsedCooldown < HackableAttribute::SharedStateMap[key].cooldown)
		{
			HackableAttribute::SharedStateMap[key].elapsedCooldown += dt;
		}
	}
}

std::string HackableAttribute::getHackableIdentifier()
{
	return this->hackableIdentifier;
}

void HackableAttribute::CleanUpGlobalState()
{
	HackableAttribute::HackTimersPaused = false;

	for (auto next : HackableAttribute::SharedStateMap)
	{
		// next.first->restoreState();
	}

	HackableAttribute::SharedStateMap.clear();
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
	SharedState* state = this->getSharedState();

	return state == nullptr ? 0.0f : state->elapsedDuration;
}

float HackableAttribute::getDuration()
{
	SharedState* state = this->getSharedState();

	return state == nullptr ? 0.0f : state->duration;
}

bool HackableAttribute::isComplete()
{
	return this->getElapsedDuration() >= this->getDuration();
}

bool HackableAttribute::isCooldownComplete()
{
	return this->getElapsedCooldown() >= this->getCooldown();
}

float HackableAttribute::getElapsedCooldown()
{
	SharedState* state = this->getSharedState();

	return state == nullptr ? 0.0f : state->elapsedCooldown;
}

float HackableAttribute::getCooldown()
{
	SharedState* state = this->getSharedState();

	return state == nullptr ? 0.0f : state->cooldown;
}

std::string HackableAttribute::getHackBarResource()
{
	switch(this->getHackBarColor())
	{
		case HackableAttribute::HackBarColor::Blue:
		{
			return UIResources::HUD_FillBlue;
		}
		case HackableAttribute::HackBarColor::Gray:
		{
			return UIResources::HUD_FillGray;
		}
		case HackableAttribute::HackBarColor::Green:
		{
			return UIResources::HUD_FillGreen;
		}
		case HackableAttribute::HackBarColor::Orange:
		{
			return UIResources::HUD_FillOrange;
		}
		case HackableAttribute::HackBarColor::Pink:
		{
			return UIResources::HUD_FillPink;
		}
		case HackableAttribute::HackBarColor::Red:
		{
			return UIResources::HUD_FillRed;
		}
		case HackableAttribute::HackBarColor::Teal:
		{
			return UIResources::HUD_FillTeal;
		}
		case HackableAttribute::HackBarColor::Yellow:
		{
			return UIResources::HUD_FillYellow;
		}
		default:
		case HackableAttribute::HackBarColor::Purple:
		{
			return UIResources::HUD_FillPurple;
		}
	}
}

HackableAttribute::HackBarColor HackableAttribute::getHackBarColor()
{
	return this->hackBarColor;
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

void HackableAttribute::restoreState()
{
}

void HackableAttribute::restoreStateIfUnique()
{
	// Some example scenarios of why this is needed:
	// 1) A buff with a hackable is removed, and this was the only hackable (ie only 1 buff, 1 hackable code). Restore the state.
	// 2) A buff with a hackable is removed, but another mob has the same buff, thus we should be waiting on the duration before restoring the state.

	HackableEvents::HackableAttributeQueryArgs queryArgs = HackableEvents::HackableAttributeQueryArgs(this->getHackableIdentifier());

	HackableEvents::TriggerQueryAttributeCount(&queryArgs);
	
	if (queryArgs.count <= 1)
	{
		this->restoreState();
	}
}

void HackableAttribute::resetTimer()
{
	HackableAttribute::SharedStateMap[this->getHackableIdentifier()].elapsedDuration = 0.0f;
	HackableAttribute::SharedStateMap[this->getHackableIdentifier()].elapsedCooldown = 0.0f;
}

void HackableAttribute::TryRegisterSharedState(HackableAttribute* attribute, SharedState sharedState)
{
	if (HackableAttribute::SharedStateMap.find(attribute->getHackableIdentifier()) == HackableAttribute::SharedStateMap.end())
	{
		HackableAttribute::SharedStateMap[attribute->getHackableIdentifier()] = sharedState;
	}
}

HackableAttribute::SharedState* HackableAttribute::getSharedState()
{
	if (HackableAttribute::SharedStateMap.find(this->getHackableIdentifier()) != HackableAttribute::SharedStateMap.end())
	{
		return &HackableAttribute::SharedStateMap[this->getHackableIdentifier()];
	}

	return nullptr;
}
