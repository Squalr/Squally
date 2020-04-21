#include "HackableObject.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackActivatedAbility.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
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
unsigned long long HackableObject::WatchId = 0;

HackableObject::HackableObject() : HackableObject(ValueMap())
{
}

HackableObject::HackableObject(const ValueMap& properties) : super(properties)
{
	this->hackableList = std::vector<HackableBase*>();
	this->codeList = std::vector<HackableCode*>();
	this->hackAbilityList = std::vector<HackActivatedAbility*>();
	this->trackedAttributes = std::vector<HackableBase*>();
	this->uiElementsButton = Node::create();
	this->uiElementsRain = Node::create();
	this->uiElementsProgressBars = Node::create();
	this->hackButton = HackButton::create();
	this->timeRemainingIcons = std::vector<Sprite*>();
	this->timeRemainingBars = std::vector<ProgressBar*>();
	this->clippyMap = std::map<std::string, std::function<Clippy*()>>();
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

	this->uiElementsButton->addChild(this->hackButton);
	this->uiElementsRain->addChild(this->hackParticlesNode);
	this->addChild(this->uiElementsRain);
	this->addChild(this->uiElementsButton);
	this->addChild(this->uiElementsProgressBars);
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

	this->uiElementsButton->setPosition(this->getButtonOffset());
	this->uiElementsRain->setPosition(this->getRainOffset());
	this->uiElementsProgressBars->setPosition(this->getProgressBarsOffset());

	if (!this->hackableList.empty())
	{	
		// Note that this is deferred until now as an optimization, as TriggerBindObjectToUI is expensive
		if (!this->hasRelocatedUI)
		{
			// Move the UI elements to the top-most layer
			ObjectEvents::TriggerBindObjectToUI(ObjectEvents::RelocateObjectArgs(this->uiElementsButton));
			ObjectEvents::TriggerBindObjectToUI(ObjectEvents::RelocateObjectArgs(this->uiElementsRain));
			ObjectEvents::TriggerBindObjectToUI(ObjectEvents::RelocateObjectArgs(this->uiElementsProgressBars));
			this->hasRelocatedUI = true;
		}
	}

	this->updateTimeRemainingBars();
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

	// Abort if all hackables off cooldown
	if (std::all_of(this->hackableList.begin(), this->hackableList.end(), [=](HackableBase* attribute)
		{
			return (!attribute->isCooldownComplete());
		}))
	{
		return;
	}

	// Enable if any hackable is off cooldown and unlocked (right hack flags are set)
	if (std::any_of(this->hackableList.begin(), this->hackableList.end(), [=](HackableBase* attribute)
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
		ObjectEvents::TriggerReparentBind(ObjectEvents::ReparentBindArgs(this->uiElementsRain, newParent));
		ObjectEvents::TriggerReparentBind(ObjectEvents::ReparentBindArgs(this->uiElementsButton, newParent));
		ObjectEvents::TriggerReparentBind(ObjectEvents::ReparentBindArgs(this->uiElementsProgressBars, newParent));
	});
}

void HackableObject::registerHackables()
{
}

void HackableObject::updateTimeRemainingBars()
{
	// Add attributes that should be tracked by the UI (activated or on CD)
	for (auto next : this->hackableList)
	{
		if (std::find(this->trackedAttributes.begin(), this->trackedAttributes.end(), next) == this->trackedAttributes.end())
		{
			if (!next->isComplete() || !next->isCooldownComplete())
			{
				this->trackedAttributes.push_back(next);
			}
		}
	}

	// Remove attributes that have timed out and are available cooldown wise
	this->trackedAttributes.erase(std::remove_if(this->trackedAttributes.begin(), this->trackedAttributes.end(), [](HackableBase* attribute)
	{
		return attribute->isComplete() && attribute->isCooldownComplete();
	}), this->trackedAttributes.end());

	while (this->timeRemainingBars.size() < this->trackedAttributes.size())
	{
		ProgressBar* progressBar = ProgressBar::create(UIResources::HUD_StatFrame, UIResources::HUD_FillPurple);
		Sprite* icon = Sprite::create();

		this->timeRemainingBars.push_back(progressBar);
		this->timeRemainingIcons.push_back(icon);

		this->uiElementsProgressBars->addChild(progressBar);
		this->uiElementsProgressBars->addChild(icon);
	}

	int attributeCount = int(this->trackedAttributes.size());

	for (int index = 0; index < int(this->timeRemainingBars.size()); index++)
	{
		if (index < attributeCount)
		{
			auto next = this->trackedAttributes[index];

			this->timeRemainingBars[index]->setVisible(true);
			this->timeRemainingIcons[index]->setVisible(true);
			
			if (this->timeRemainingIcons[index]->getResourceName() != next->getIconResource())
			{
				this->timeRemainingIcons[index]->initWithFile(next->getIconResource());
				this->timeRemainingIcons[index]->setScale(0.5f);
			}

			if (this->timeRemainingBars[index]->getFillSprite()->getResourceName() != next->getHackBarResource())
			{
				this->timeRemainingBars[index]->getFillSprite()->initWithFile(next->getHackBarResource());
			}

			this->timeRemainingBars[index]->setPositionY(float(index) * -32.0f);
			this->timeRemainingIcons[index]->setPosition(Vec2(-80.0f, float(index) * -32.0f));

			this->timeRemainingBars[index]->setProgress(1.0f - next->getElapsedDuration() / next->getDuration());
		}
		else
		{
			this->timeRemainingBars[index]->setVisible(false);
			this->timeRemainingIcons[index]->setVisible(false);
		}
	}

	this->refreshParticleFx();
}

void HackableObject::refreshParticleFx()
{
	if (std::any_of(this->hackableList.begin(), this->hackableList.end(), [=](HackableBase* attribute)
		{
			return (attribute->getRequiredHackFlag() & HackableObject::HackFlags) == attribute->getRequiredHackFlag();
		})
		&& this->allowFx
		&& this->isHackable
		&& !this->hackableList.empty()
		&& this->trackedAttributes.empty())
	{
		this->createSensingParticles();

		if (!hackParticles1->isActive())
		{
			this->hackParticles1->start();
		}

		if (!hackParticles2->isActive())
		{
			this->hackParticles2->start();
			this->hackParticles2->accelerate(1.0f);
		}

		if (!hackParticles3->isActive())
		{
			this->hackParticles3->start();
		}

		if (!hackParticles4->isActive())
		{
			this->hackParticles4->start();
			this->hackParticles4->accelerate(1.0f);
		}

		if (!hackParticles5->isActive())
		{
			this->hackParticles5->start();
		}
	}
	else if (this->hackParticles1 != nullptr)
	{
		this->hackParticles1->stop(1.5f);
		this->hackParticles2->stop(1.5f);
		this->hackParticles3->stop(1.5f);
		this->hackParticles4->stop(1.5f);
		this->hackParticles5->stop(1.5f);
	}

	if (std::any_of(this->trackedAttributes.begin(), this->trackedAttributes.end(), [=](HackableBase* attribute)
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
	// By default just put this where the button is. Inheriting objects can override if needed.
	return this->getButtonOffset();
}

Vec2 HackableObject::getButtonOffset()
{
	return Vec2::ZERO;
}

cocos2d::Vec2 HackableObject::getProgressBarsOffset()
{
	// By default just put this where the button is. Inheriting objects can override if needed.
	return this->getButtonOffset();
}

void HackableObject::onHackableClick()
{
	HackableEvents::TriggerOpenHackable(HackableEvents::HackableObjectOpenArgs(this, HackableObject::HackFlags));
}

HackablePreview* HackableObject::createDefaultPreview()
{
	return nullptr;
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

	this->hackableList.push_back(hackableCode);
	this->codeList.push_back(hackableCode);

	this->refreshParticleFx();
}

void HackableObject::unregisterAllHackables(bool forceRestoreState)
{
	auto codeListClone = this->codeList;
	auto hackAbilityListClone = this->hackAbilityList;

	for (auto next : codeListClone)
	{
		this->unregisterCode(next, forceRestoreState);
	}

	for (auto next : hackAbilityListClone)
	{
		this->unregisterHackAbility(next);
	}
}

void HackableObject::unregisterCode(HackableCode* hackableCode, bool forceRestoreState)
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
		if (forceRestoreState)
		{
			hackableCode->restoreState();
		}
		else
		{
			hackableCode->restoreStateIfUnique();
		}
		
		// Removed all tracked attributes with the same ID as the code being removed
		this->trackedAttributes.erase(std::remove_if(this->trackedAttributes.begin(), this->trackedAttributes.end(), [=](HackableBase* attribute)
		{
			return attribute->getHackableIdentifier() == hackableCode->getHackableIdentifier();
		}), this->trackedAttributes.end());

		this->hackableList.erase(std::remove(this->hackableList.begin(), this->hackableList.end(), hackableCode), this->hackableList.end());
		this->codeList.erase(std::remove(this->codeList.begin(), this->codeList.end(), hackableCode), this->codeList.end());

		this->refreshParticleFx();
	}
}

void HackableObject::registerHackAbility(HackActivatedAbility* hackActivatedAbility)
{
	if (hackActivatedAbility == nullptr)
	{
		return;
	}
	
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

	// Removed all tracked attributes with the same ID as the ability being removed
	this->trackedAttributes.erase(std::remove_if(this->trackedAttributes.begin(), this->trackedAttributes.end(), [=](HackableBase* attribute)
	{
		return attribute->getHackableIdentifier() == hackActivatedAbility->getHackableIdentifier();
	}), this->trackedAttributes.end());

	this->hackableList.erase(std::remove(this->hackableList.begin(), this->hackableList.end(), hackActivatedAbility), this->hackableList.end());
	this->hackAbilityList.erase(std::remove(this->hackAbilityList.begin(), this->hackAbilityList.end(), hackActivatedAbility), this->hackAbilityList.end());
	
	this->refreshParticleFx();
}

void HackableObject::registerClippyOnto(std::string identifier, std::function<Clippy*()> clippyFunc)
{
	this->clippyMap[identifier] = clippyFunc;
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

void HackableObject::onDespawn()
{
	super::onDespawn();

	this->unregisterAllHackables();
}
