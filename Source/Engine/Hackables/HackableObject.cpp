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

int HackableObject::HackFlags = 0;

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
		float highestRatio = 0.0f;

		if (!this->timeRemainingBar->isVisible())
		{
			this->timeRemainingBar->setVisible(true);
			this->refreshParticleFx();
		}

		// Remove attributes that have timed out
		this->trackedAttributes.erase(std::remove_if(this->trackedAttributes.begin(), this->trackedAttributes.end(), [](HackableAttribute* attribute)
		{
			return attribute->getElapsedDuration() >= attribute->getDuration();
		}), this->trackedAttributes.end());

		if (this->trackedAttributes.empty())
		{
			this->timeRemainingBar->setVisible(false);
			this->refreshParticleFx();
		}

		// If multiple hacks are enabled, just pick the highest ratio for now
		for (auto it = this->trackedAttributes.begin(); it != this->trackedAttributes.end(); it++)
		{
			highestRatio = std::max(highestRatio, (*it)->getElapsedDuration() / (*it)->getDuration());
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
}

void HackableObject::toggleAllowFx(bool allowFx)
{
	this->allowFx = allowFx;

	this->refreshParticleFx();
}

void HackableObject::onHackerModeEnable()
{
	super::onHackerModeEnable();

	if (!this->isHackable)
	{
		return;
	}

	// Enable if any hackable is unlocked
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
	if (this->allowFx && !this->hackableList.empty() && this->trackedAttributes.empty())
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

void HackableObject::unregisterAllHackables()
{
	std::vector<HackableCode*> codeList = this->codeList;

	for (auto next : codeList)
	{
		this->unregisterCode(next);
	}

	std::vector<HackableData*> dataList = this->dataList;

	for (auto next : dataList)
	{
		this->unregisterData(next);
	}

	std::vector<HackActivatedAbility*> hackAbilityList = this->hackAbilityList;

	for (auto next : hackAbilityList)
	{
		this->unregisterHackAbility(next);
	}
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

	this->refreshParticleFx();
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

Node* HackableObject::getHackParticlesNode()
{
	return this->hackParticlesNode;
}
