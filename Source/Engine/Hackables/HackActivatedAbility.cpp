#include "HackActivatedAbility.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/GlobalHackAttributeContainer.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

HackActivatedAbility* HackActivatedAbility::create(
	std::string hackableIdentifier,
	std::function<void()> onActivate,
	std::function<void()> onDeactivate,
	int hackFlags,
	float duration,
	HackBarColor hackBarColor,
	std::string iconResource,
	LocalizedString* name,
	HackablePreview* hackablePreview,
	Clippy* clippy)
{
	HackActivatedAbility* instance = GlobalHackAttributeContainer::GetHackActivatedAbility(hackableIdentifier);

	if (instance == nullptr)
	{
		instance = new HackActivatedAbility(hackableIdentifier, onActivate, onDeactivate, hackFlags, duration, hackBarColor, iconResource, name, hackablePreview, clippy);
		instance->autorelease();

		GlobalHackAttributeContainer::RegisterHackActivatedAbility(instance);
	}

	return instance;
}

HackActivatedAbility::HackActivatedAbility(
	std::string hackableIdentifier,
	std::function<void()> onActivate,
	std::function<void()> onDeactivate,
	int hackFlags,
	float duration,
	HackBarColor hackBarColor,
	std::string iconResource,
	LocalizedString* name,
	HackablePreview* hackablePreview,
	Clippy* clippy)
	: HackableBase(
		hackableIdentifier,
		hackFlags,
		duration,
		0.0f,
		hackBarColor,
		iconResource,
		name,
		hackablePreview)
{
	this->onActivate = onActivate;
	this->onDeactivate = onDeactivate;
}

HackActivatedAbility::~HackActivatedAbility()
{
}

void HackActivatedAbility::activate()
{
	if (this->onActivate != nullptr)
	{
		this->onActivate();
	}

	HackableEvents::TriggerOnHackApplied(HackableEvents::HackAppliedArgs(this));
	this->startTimer();
}

void HackActivatedAbility::restoreState()
{
	super::restoreState();
	
	if (this->onDeactivate != nullptr)
	{
		this->onDeactivate();
	}
}
