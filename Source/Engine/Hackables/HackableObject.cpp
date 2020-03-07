#include "HackableObject.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/Clippy.h"
#include "Engine/Hackables/HackActivatedAbility.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Hackables/HackButton.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/FXResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

int HackableObject::HackFlags = 0;

HackableObject::HackableObject() : HackableObject(ValueMap())
{
}

HackableObject::HackableObject(const ValueMap& properties) : super(properties)
{
	this->hackableList = std::vector<HackableAttribute*>();
	this->codeList = std::vector<HackableCode*>();
	this->hackAbilityList = std::vector<HackActivatedAbility*>();
	this->trackedAttributes = std::vector<HackableAttribute*>();
	this->clippyList = std::vector<Clippy*>();
	this->uiElements = Node::create();
	this->uiElementsRain = Node::create();
	this->hackButton = HackButton::create();
	this->hackablesNode = Node::create();
	this->timeRemainingBar = ProgressBar::create(UIResources::HUD_StatFrame, UIResources::HUD_HackBarFill);
	this->hasRelocatedUI = false;
	this->isHackable = true;
	this->allowFx = true;
	this->hackParticlesNode = Node::create();
	this->hackParticles1 = nullptr;
	this->hackParticles2 = nullptr;
	this->hackParticles3 = nullptr;
	this->hackParticles4 = nullptr;
	this->hackParticles5 = nullptr;
	this->hackCircle = nullptr;

	this->hackButton->setVisible(false);
	this->timeRemainingBar->setVisible(false);

	this->uiElements->addChild(this->hackButton);
	this->uiElements->addChild(this->timeRemainingBar);
	this->uiElementsRain->addChild(this->hackParticlesNode);
	this->addChild(this->hackablesNode);
	this->addChild(this->uiElementsRain);
	this->addChild(this->uiElements);
}

HackableObject::~HackableObject()
{
}

void HackableObject::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void HackableObject::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->hackButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->onHackableClick();
	});

	this->registerHackables();
}

void HackableObject::onExit()
{
	super::onExit();

	this->unregisterAllHackables();
}

void HackableObject::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackApplied, [=](EventCustom* eventCustom)
	{
		HackableEvents::HackAppliedArgs* args = static_cast<HackableEvents::HackAppliedArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			for (auto next : this->hackableList)
			{
				if (next->getPointer() == args->activeAttribute->getPointer())
				{
					this->trackedAttributes.push_back(args->activeAttribute);

					return;
				}
			}
		}
	}));
	
	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackFlagsChanged, [=](EventCustom* eventCustom)
	{
		this->refreshParticleFx();
	}));
}

void HackableObject::initializePositions()
{
	super::initializePositions();
}

void HackableObject::update(float dt)
{
	super::update(dt);

	this->uiElements->setPosition(this->getButtonOffset());
	this->uiElementsRain->setPosition(this->getRainOffset());

	if (!this->hackableList.empty())
	{	
		// Note that this is deferred until now as an optimization, as TriggerBindObjectToUI is expensive
		if (!this->hasRelocatedUI)
		{
			// Move the UI elements to the top-most layer
			ObjectEvents::TriggerBindObjectToUI(ObjectEvents::RelocateObjectArgs(this->uiElements));
			ObjectEvents::TriggerBindObjectToUI(ObjectEvents::RelocateObjectArgs(this->uiElementsRain));
			this->hasRelocatedUI = true;
		}
	}

	if (!this->trackedAttributes.empty())
	{
		// Remove attributes that have timed out and are available cooldown wise
		this->trackedAttributes.erase(std::remove_if(this->trackedAttributes.begin(), this->trackedAttributes.end(), [](HackableAttribute* attribute)
		{
			return (attribute->getElapsedDuration() >= attribute->getDuration()) && attribute->isCooldownComplete();
		}), this->trackedAttributes.end());

		bool allComplete = std::all_of(this->trackedAttributes.begin(), this->trackedAttributes.end(), [=](HackableAttribute* attribute)
			{
				return (attribute->getElapsedDuration() >= attribute->getDuration());
			});

		// Show/hide progress bar depending if durations are complete
		if (allComplete && this->timeRemainingBar->isVisible())
		{
			this->timeRemainingBar->setVisible(false);
			this->refreshParticleFx();
		}
		else if (!allComplete && !this->timeRemainingBar->isVisible())
		{
			this->timeRemainingBar->setVisible(true);
			this->refreshParticleFx();
		}

		// All attributes removed! Refresh PFX
		if (this->trackedAttributes.empty())
		{
			this->refreshParticleFx();
		}

		float highestRatio = 0.0f;

		// If multiple hacks are enabled, just pick the highest ratio for now
		for (auto next : this->trackedAttributes)
		{
			highestRatio = std::max(highestRatio, next->getElapsedDuration() / next->getDuration());
		}

		this->timeRemainingBar->setProgress(1.0f - highestRatio);
	}
}

int HackableObject::GetHackFlags()
{
	return HackableObject::HackFlags;
}

void HackableObject::SetHackFlags(int hackFlags)
{
	HackableObject::HackFlags = hackFlags;

	HackableEvents::TriggerHackFlagsChanged(HackableEvents::HackFlagsChangedArgs(HackableObject::HackFlags));
}

void HackableObject::toggleHackable(bool isHackable)
{
	this->isHackable = isHackable;

	this->refreshParticleFx();
}

void HackableObject::toggleAllowFx(bool allowFx)
{
	this->allowFx = allowFx;

	this->refreshParticleFx();
}

void HackableObject::onHackerModeEnable()
{
	super::onHackerModeEnable();

	if (!this->isHackable || this->hackableList.empty())
	{
		return;
	}

	// Abort if any hackable is off cooldown (Another option for future: only abort if all are off-cooldown, and have radial menu show individual cooldowns)
	if (std::any_of(this->hackableList.begin(), this->hackableList.end(), [=](HackableAttribute* attribute)
		{
			return (!attribute->isCooldownComplete());
		}))
	{
		return;
	}

	// Enable if any hackable is off cooldown and unlocked (right hack flags are set)
	if (std::any_of(this->hackableList.begin(), this->hackableList.end(), [=](HackableAttribute* attribute)
		{
			return (attribute->getRequiredHackFlag() & HackableObject::HackFlags) == attribute->getRequiredHackFlag();
		}))
	{
		this->hackButton->setVisible(true);
	}
}

void HackableObject::onHackerModeDisable()
{
	super::onHackerModeDisable();

	this->hackButton->setVisible(false);
}

void HackableObject::rebindUIElementsTo(cocos2d::Node* newParent)
{
	this->defer([=]()
	{
		ObjectEvents::TriggerReparentBind(ObjectEvents::ReparentBindArgs(this->uiElements, newParent));
	});
}

void HackableObject::registerHackables()
{
}

void HackableObject::refreshParticleFx()
{
	if (this->allowFx && this->isHackable && !this->hackableList.empty() && this->trackedAttributes.empty())
	{
		this->createSensingParticles();
		this->hackParticles1->start();
		this->hackParticles2->start();
		this->hackParticles3->start();
		this->hackParticles4->start();
		this->hackParticles5->start();

		this->hackParticles2->accelerate(1.0f);
		this->hackParticles4->accelerate(1.0f);
	}
	else if (this->hackParticles1 != nullptr)
	{
		this->hackParticles1->stop(1.5f);
		this->hackParticles2->stop(1.5f);
		this->hackParticles3->stop(1.5f);
		this->hackParticles4->stop(1.5f);
		this->hackParticles5->stop(1.5f);
	}

	if (std::any_of(this->trackedAttributes.begin(), this->trackedAttributes.end(), [=](HackableAttribute* attribute)
		{
			return (!attribute->isCooldownComplete());
		}))
	{
		this->createHackCircle();
		this->hackCircle->stopAllActions();
		this->hackCircle->runAction(RepeatForever::create(RotateBy::create(5.0f, 360.0f)));
		this->hackCircle->runAction(FadeTo::create(0.75f, 255));
	}
	else if (this->hackCircle != nullptr)
	{
		this->hackCircle->runAction(FadeTo::create(0.75f, 0));
	}
}

Vec2 HackableObject::getRainOffset()
{
	return Vec2::ZERO;
}

Vec2 HackableObject::getButtonOffset()
{
	return Vec2::ZERO;
}

void HackableObject::onHackableClick()
{
	HackableEvents::TriggerOpenHackable(HackableEvents::HackableObjectOpenArgs(this, HackableObject::HackFlags));
}

HackablePreview* HackableObject::createDefaultPreview()
{
	return nullptr;
}

void HackableObject::unregisterAllHackables()
{
	std::vector<HackableCode*> codeList = this->codeList;

	for (auto next : codeList)
	{
		this->unregisterCode(next);
	}

	std::vector<HackActivatedAbility*> hackAbilityList = this->hackAbilityList;

	for (auto next : hackAbilityList)
	{
		this->unregisterHackAbility(next);
	}
}

void HackableObject::registerCode(HackableCode* hackableCode)
{
	if (hackableCode == nullptr)
	{
		return;
	}

	for (auto next : this->codeList)
	{
		if (next->getPointer() == hackableCode->getPointer())
		{
			return;
		}
	}

	this->hackablesNode->addChild(hackableCode);
	this->hackableList.push_back(hackableCode);
	this->codeList.push_back(hackableCode);

	this->refreshParticleFx();
}

void HackableObject::unregisterCode(HackableCode* hackableCode)
{
	bool hasHackableCode = false;

	if (hackableCode == nullptr)
	{
		return;
	}

	for (auto next : this->codeList)
	{
		if (next->getPointer() == hackableCode->getPointer())
		{
			hackableCode = next;
			hasHackableCode = true;
			break;
		}
	}

	if (hasHackableCode)
	{
		hackableCode->restoreState();

		this->hackableList.erase(std::remove(this->hackableList.begin(), this->hackableList.end(), hackableCode), this->hackableList.end());
		this->codeList.erase(std::remove(this->codeList.begin(), this->codeList.end(), hackableCode), this->codeList.end());

		this->hackablesNode->removeChild(hackableCode);

		this->refreshParticleFx();
	}
}

void HackableObject::registerHackAbility(HackActivatedAbility* hackActivatedAbility)
{
	if (hackActivatedAbility == nullptr)
	{
		return;
	}

	this->hackablesNode->addChild(hackActivatedAbility);
	this->hackableList.push_back(hackActivatedAbility);
	this->hackAbilityList.push_back(hackActivatedAbility);
	
	this->refreshParticleFx();
}

void HackableObject::unregisterHackAbility(HackActivatedAbility* hackActivatedAbility)
{
	if (hackActivatedAbility == nullptr)
	{
		return;
	}

	this->hackablesNode->removeChild(hackActivatedAbility);

	this->hackableList.erase(std::remove(this->hackableList.begin(), this->hackableList.end(), hackActivatedAbility), this->hackableList.end());
	this->hackAbilityList.erase(std::remove(this->hackAbilityList.begin(), this->hackAbilityList.end(), hackActivatedAbility), this->hackAbilityList.end());
	
	this->refreshParticleFx();
}

void HackableObject::enableAllClippy()
{
	for (auto next : this->clippyList)
	{
		next->setIsEnabled(true);
	}
}

void HackableObject::registerClippy(Clippy* clippy)
{
	if (clippy != nullptr)
	{
		this->clippyList.push_back(clippy);
		this->addChild(clippy);
	}
}

void HackableObject::createSensingParticles()
{
	if (this->hackParticles1 == nullptr)
	{
		this->hackParticles1 = SmartParticles::create(ParticleResources::Platformer_Hacking_HackerRain1, SmartParticles::CullInfo(Size(128.0f, 128.0f)));
		this->hackParticles2 = SmartParticles::create(ParticleResources::Platformer_Hacking_HackerRain2, SmartParticles::CullInfo(Size(128.0f, 128.0f)));
		this->hackParticles3 = SmartParticles::create(ParticleResources::Platformer_Hacking_HackerRain3, SmartParticles::CullInfo(Size(128.0f, 128.0f)));
		this->hackParticles4 = SmartParticles::create(ParticleResources::Platformer_Hacking_HackerRain4, SmartParticles::CullInfo(Size(128.0f, 128.0f)));
		this->hackParticles5 = SmartParticles::create(ParticleResources::Platformer_Hacking_HackerRain5, SmartParticles::CullInfo(Size(128.0f, 128.0f)));

		this->hackParticlesNode->addChild(this->hackParticles1);
		this->hackParticlesNode->addChild(this->hackParticles2);
		this->hackParticlesNode->addChild(this->hackParticles3);
		this->hackParticlesNode->addChild(this->hackParticles4);
		this->hackParticlesNode->addChild(this->hackParticles5);
	}
}

void HackableObject::createHackCircle()
{
	if (this->hackCircle == nullptr)
	{
		this->hackCircle = Sprite::create(FXResources::HackerCircle);

		this->hackParticlesNode->addChild(this->hackCircle);
	}
}

Node* HackableObject::getHackParticlesNode()
{
	return this->hackParticlesNode;
}
