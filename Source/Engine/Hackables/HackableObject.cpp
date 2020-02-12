#include "HackableObject.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/Clippy.h"
#include "Engine/Hackables/HackActivatedAbility.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Hackables/HackButton.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

HackableObject::HackableObject() : HackableObject(ValueMap())
{
}

HackableObject::HackableObject(const ValueMap& properties) : super(properties)
{
	this->hackableList = std::vector<HackableAttribute*>();
	this->dataList = std::vector<HackableData*>();
	this->codeList = std::vector<HackableCode*>();
	this->hackAbilityList = std::vector<HackActivatedAbility*>();
	this->trackedAttributes = std::vector<HackableAttribute*>();
	this->clippyList = std::vector<Clippy*>();
	this->uiElements = Node::create();
	this->hackButton = HackButton::create();
	this->hackablesNode = Node::create();
	this->timeRemainingBar = ProgressBar::create(UIResources::HUD_StatFrame, UIResources::HUD_HackBarFill);
	this->hasRelocatedUI = false;
	this->isHackable = true;
	this->sensingParticlesNode = Node::create();
	this->sensingParticles = nullptr;
	this->cachedHackFlags = 0;

	this->hackButton->setVisible(false);
	this->timeRemainingBar->setVisible(false);

	this->uiElements->addChild(this->sensingParticlesNode);
	this->uiElements->addChild(this->hackButton);
	this->uiElements->addChild(this->timeRemainingBar);
	this->addChild(this->hackablesNode);
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

void HackableObject::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackApplied, [=](EventCustom* eventCustom)
	{
		HackableEvents::HackAppliedArgs* args = static_cast<HackableEvents::HackAppliedArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			for (auto it = this->hackableList.begin(); it != this->hackableList.end(); it++)
			{
				if ((*it)->getPointer() == args->activeAttribute->getPointer())
				{
					this->trackedAttributes.push_back(args->activeAttribute);

					return;
				}
			}
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventSensingEnable, [=](EventCustom* eventCustom)
	{
		HackableEvents::SensingArgs* args = static_cast<HackableEvents::SensingArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->onSensingEnable(args->hackFlags);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventSensingDisable, [=](EventCustom*)
	{
		this->onSensingDisable();
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

	if (!this->hackableList.empty())
	{	
		// Note that this is deferred until now as an optimization, as TriggerBindObjectToUI is expensive
		if (!this->hasRelocatedUI)
		{
			// Move the UI elements to the top-most layer
			ObjectEvents::TriggerBindObjectToUI(ObjectEvents::RelocateObjectArgs(this->uiElements));
			this->hasRelocatedUI = true;
		}
	}
	
	if (!this->trackedAttributes.empty())
	{
		float highestRatio = 0.0f;

		if (!this->timeRemainingBar->isVisible())
		{
			this->timeRemainingBar->setVisible(true);
		}

		// Remove attributes that have timed out
		this->trackedAttributes.erase(std::remove_if(this->trackedAttributes.begin(), this->trackedAttributes.end(), [](HackableAttribute* attribute)
		{
			return attribute->getElapsedDuration() >= attribute->getDuration();
		}), this->trackedAttributes.end());

		if (this->trackedAttributes.empty())
		{
			this->timeRemainingBar->setVisible(false);
		}

		// If multiple hacks are enabled, just pick the highest ratio for now
		for (auto it = this->trackedAttributes.begin(); it != this->trackedAttributes.end(); it++)
		{
			highestRatio = std::max(highestRatio, (*it)->getElapsedDuration() / (*it)->getDuration());
		}

		this->timeRemainingBar->setProgress(1.0f - highestRatio);
	}
}

void HackableObject::toggleHackable(bool isHackable)
{
	this->isHackable = isHackable;
}

void HackableObject::onHackerModeEnable(int hackFlags)
{
	super::onHackerModeEnable(hackFlags);

	if (!this->isHackable)
	{
		return;
	}

	// Enable if any hackable is unlocked
	if (std::any_of(this->hackableList.begin(), this->hackableList.end(), [=](HackableAttribute* attribute)
		{
			return (attribute->getRequiredHackFlag() & hackFlags) == attribute->getRequiredHackFlag();
		}))
	{
		this->hackButton->setVisible(true);
	}

	this->cachedHackFlags = hackFlags;
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

void HackableObject::onSensingEnable(int hackFlags)
{
	if (!this->isHackable)
	{
		return;
	}

	for (auto it = this->hackableList.begin(); it != this->hackableList.end(); it++)
	{
		if (((*it)->getRequiredHackFlag() & hackFlags) != (*it)->getRequiredHackFlag())
		{
			return;
		}
	}

	if (!this->hackableList.empty())
	{
		this->getSensingParticles()->start();
	}
}

void HackableObject::onSensingDisable()
{
	if (this->sensingParticles != nullptr)
	{
		this->getSensingParticles()->stop(1.5f);
	}
}

void HackableObject::registerHackables()
{
}

Vec2 HackableObject::getButtonOffset()
{
	return Vec2::ZERO;
}

void HackableObject::onHackableClick()
{
	HackableEvents::TriggerOpenHackable(HackableEvents::HackableObjectOpenArgs(this, this->cachedHackFlags));
}

HackablePreview* HackableObject::createDefaultPreview()
{
	return nullptr;
}

void HackableObject::registerData(HackableData* hackableData)
{
	if (hackableData == nullptr)
	{
		return;
	}
	
	for (auto it = this->dataList.begin(); it != this->dataList.end(); it++)
	{
		if ((*it)->getPointer() == hackableData->getPointer())
		{
			return;
		}
	}

	this->hackablesNode->addChild(hackableData);
	this->hackableList.push_back(hackableData);
	this->dataList.push_back(hackableData);
}

void HackableObject::unregisterData(HackableData* hackableData)
{
	if (hackableData == nullptr)
	{
		return;
	}

	this->hackablesNode->removeChild(hackableData);

	this->hackableList.erase(std::remove(this->hackableList.begin(), this->hackableList.end(), hackableData), this->hackableList.end());
	this->dataList.erase(std::remove(this->dataList.begin(), this->dataList.end(), hackableData), this->dataList.end());
}

void HackableObject::registerCode(HackableCode* hackableCode)
{
	if (hackableCode == nullptr)
	{
		return;
	}

	for (auto it = this->codeList.begin(); it != this->codeList.end(); it++)
	{
		if ((*it)->getPointer() == hackableCode->getPointer())
		{
			return;
		}
	}

	this->hackablesNode->addChild(hackableCode);
	this->hackableList.push_back(hackableCode);
	this->codeList.push_back(hackableCode);
}

void HackableObject::unregisterCode(HackableCode* hackableCode)
{
	bool hasHackableCode = false;

	if (hackableCode == nullptr)
	{
		return;
	}

	for (auto it = this->codeList.begin(); it != this->codeList.end(); it++)
	{
		if ((*it)->getPointer() == hackableCode->getPointer())
		{
			hackableCode = *it;
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

SmartParticles* HackableObject::getSensingParticles()
{
	if (this->sensingParticles == nullptr)
	{
		this->sensingParticles = SmartParticles::create(ParticleResources::HackableGlow, SmartParticles::CullInfo(Size(128.0f, 128.0f)));

		this->sensingParticlesNode->addChild(this->sensingParticles);
	}
	
	return this->sensingParticles;
}
