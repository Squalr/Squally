#include "HackActivatedAbility.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

HackActivatedAbility* HackActivatedAbility::create(std::function<void()> onActivate, std::function<void()> onDeactivate, int requiredEq, float duration, std::string iconResource, LocalizedString* name, HackablePreview* hackablePreview, Clippy* clippy)
{
	HackActivatedAbility* instance = new HackActivatedAbility(onActivate, onDeactivate, requiredEq, duration, iconResource, name, hackablePreview, clippy);

	instance->autorelease();

	return instance;
}

HackActivatedAbility::HackActivatedAbility(std::function<void()> onActivate, std::function<void()> onDeactivate, int requiredEq, float duration, std::string iconResource, LocalizedString* name, HackablePreview* hackablePreview, Clippy* clippy) : HackableAttribute(requiredEq, duration, iconResource, name, hackablePreview)
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
	this->resetTimer();
}

void HackActivatedAbility::restoreState()
{
	if (this->onDeactivate != nullptr)
	{
		this->onDeactivate();
	}
}
