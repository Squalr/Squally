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
#include "Engine/Optimization/LazyNode.h"
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
	this->trackedHackables = std::vector<HackableBase*>();
	this->uiElementsButton = Node::create();
	this->uiElementsRain = Node::create();
	this->uiElementsProgressBars = Node::create();
	this->hackButton = LazyNode<HackButton>::create(CC_CALLBACK_0(HackableObject::buildHackButton, this));
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

	this->repositionHackButtons();
}

void HackableObject::update(float dt)
{
	super::update(dt);

	if (!this->hasRelocatedUI && !this->hackableList.empty())
	{	
		// Move the UI elements to the top-most layer. Deferred until now as an optimization, as TriggerBindObjectToUI is expensive
		ObjectEvents::TriggerBindObjectToUI(RelocateObjectArgs(this->uiElementsButton));
		ObjectEvents::TriggerBindObjectToUI(RelocateObjectArgs(this->uiElementsRain));
		ObjectEvents::TriggerBindObjectToUI(RelocateObjectArgs(this->uiElementsProgressBars));

		this->hasRelocatedUI = true;
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

	HackableEvents::TriggerHackFlagsChanged(HackFlagsChangedArgs(HackableObject::HackFlags));
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
	if (std::all_of(this->hackableList.begin(), this->hackableList.end(), [=](HackableBase* hackable)
		{
			return (!hackable->isCooldownComplete());
		}))
	{
		return;
	}

	// Enable if any hackable is off cooldown and unlocked (right hack flags are set)
	if (std::any_of(this->hackableList.begin(), this->hackableList.end(), [=](HackableBase* hackable)
		{
			return (hackable->getRequiredHackFlag() & HackableObject::HackFlags) == hackable->getRequiredHackFlag();
		}))
	{
		this->hackButton->lazyGet()->setVisible(true);
	}
}

void HackableObject::onHackerModeDisable()
{
	super::onHackerModeDisable();

	this->hackButton->lazyGet()->setVisible(false);
}

void HackableObject::rebindUIElementsTo(cocos2d::Node* newParent)
{
	this->defer([=]()
	{
		ObjectEvents::TriggerReparentBind(ReparentBindArgs(this->uiElementsRain, newParent));
		ObjectEvents::TriggerReparentBind(ReparentBindArgs(this->uiElementsButton, newParent));
		ObjectEvents::TriggerReparentBind(ReparentBindArgs(this->uiElementsProgressBars, newParent));
	});
}

void HackableObject::repositionHackButtons()
{
	this->uiElementsButton->setPosition(this->getButtonOffset());
	this->uiElementsRain->setPosition(this->getRainOffset());
	this->uiElementsProgressBars->setPosition(this->getProgressBarsOffset());
}

void HackableObject::registerHackables()
{
}

void HackableObject::updateTimeRemainingBars()
{
	// Add hackables that should be tracked by the UI (activated or on CD)
	for (auto next : this->hackableList)
	{
		if (std::find(this->trackedHackables.begin(), this->trackedHackables.end(), next) == this->trackedHackables.end())
		{
			if (!next->isComplete() || !next->isCooldownComplete())
			{
				this->trackedHackables.push_back(next);
			}
		}
	}

	if (this->timeRemainingBars.empty() && this->trackedHackables.empty())
	{
		this->refreshParticleFx();
		return;
	}

	// Remove hackables that have timed out and are available cooldown wise
	this->trackedHackables.erase(std::remove_if(this->trackedHackables.begin(), this->trackedHackables.end(), [](HackableBase* hackable)
	{
		return hackable->isComplete() && hackable->isCooldownComplete();
	}), this->trackedHackables.end());

	while (this->timeRemainingBars.size() < this->trackedHackables.size())
	{
		ProgressBar* progressBar = ProgressBar::create(UIResources::HUD_StatFrame, UIResources::HUD_FillPurple);
		Sprite* icon = Sprite::create();

		this->timeRemainingBars.push_back(progressBar);
		this->timeRemainingIcons.push_back(icon);

		this->uiElementsProgressBars->addChild(progressBar);
		this->uiElementsProgressBars->addChild(icon);
	}

	int hackableCount = int(this->trackedHackables.size());

	for (int index = 0; index < int(this->timeRemainingBars.size()); index++)
	{
		if (index < hackableCount)
		{
			auto next = this->trackedHackables[index];

			this->timeRemainingBars[index]->setVisible(true);
			this->timeRemainingIcons[index]->setVisible(true);
			
			if (this->timeRemainingIcons[index]->getResourceName() != next->getIconResource())
			{
				this->timeRemainingIcons[index]->initWithFile(next->getIconResource());
				this->timeRemainingIcons[index]->setScale(0.5f);
			}

			this->timeRemainingBars[index]->setPositionY(float(index) * -32.0f);
			this->timeRemainingIcons[index]->setPosition(Vec2(-80.0f, float(index) * -32.0f));

			if (!next->isComplete())
			{
				if (this->timeRemainingBars[index]->getFillSprite()->getResourceName() != next->getHackBarResource())
				{
					this->timeRemainingBars[index]->getFillSprite()->initWithFile(next->getHackBarResource());
				}

				this->timeRemainingBars[index]->setProgress(next->getDuration() <= 0.0f ? 1.0f : (1.0f - next->getElapsedDuration() / next->getDuration()));
			}
			else if (!next->isCooldownComplete())
			{
				if (this->timeRemainingBars[index]->getFillSprite()->getResourceName() != next->getHackBarCooldownResource())
				{
					this->timeRemainingBars[index]->getFillSprite()->initWithFile(next->getHackBarCooldownResource());
				}

				this->timeRemainingBars[index]->setProgress(next->getCooldown() <= 0.0f ? 1.0f : (next->getElapsedCooldown() / next->getCooldown()));
			}
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
	if (this->allowFx
		&& this->isHackable
		&& !this->hackableList.empty()
		&& this->trackedHackables.empty()
		&& std::any_of(this->hackableList.begin(), this->hackableList.end(), [=](HackableBase* hackable)
		{
			return (hackable->getRequiredHackFlag() & HackableObject::HackFlags) == hackable->getRequiredHackFlag();
		}))
	{
		this->createHackParticles();

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
	HackableEvents::TriggerOpenHackable(HackableObjectOpenArgs(this, HackableObject::HackFlags));
}

HackablePreview* HackableObject::createDefaultPreview()
{
	return nullptr;
}

void HackableObject::registerCode(HackableCode* hackableCode, bool refreshCooldowns)
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

	if (refreshCooldowns)
	{
		hackableCode->tryRefreshCooldown();
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

	for (auto next : this->timeRemainingBars)
	{
		next->setVisible(false);
	}

	for (auto next : this->timeRemainingIcons)
	{
		next->setVisible(false);
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
		// Removed all tracked hackables with the same ID as the code being removed
		this->trackedHackables.erase(std::remove_if(this->trackedHackables.begin(), this->trackedHackables.end(), [=](HackableBase* hackable)
		{
			return hackable->getHackableIdentifier() == hackableCode->getHackableIdentifier();
		}), this->trackedHackables.end());

		this->hackableList.erase(std::remove(this->hackableList.begin(), this->hackableList.end(), hackableCode), this->hackableList.end());
		this->codeList.erase(std::remove(this->codeList.begin(), this->codeList.end(), hackableCode), this->codeList.end());

		this->refreshParticleFx();
	}
}

void HackableObject::registerHackAbility(HackActivatedAbility* hackActivatedAbility, bool refreshCooldowns)
{
	if (hackActivatedAbility == nullptr)
	{
		return;
	}

	if (refreshCooldowns)
	{
		hackActivatedAbility->tryRefreshCooldown();
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

	// Removed all tracked hackables with the same ID as the ability being removed
	this->trackedHackables.erase(std::remove_if(this->trackedHackables.begin(), this->trackedHackables.end(), [=](HackableBase* hackable)
	{
		return hackable->getHackableIdentifier() == hackActivatedAbility->getHackableIdentifier();
	}), this->trackedHackables.end());

	this->hackableList.erase(std::remove(this->hackableList.begin(), this->hackableList.end(), hackActivatedAbility), this->hackableList.end());
	this->hackAbilityList.erase(std::remove(this->hackAbilityList.begin(), this->hackAbilityList.end(), hackActivatedAbility), this->hackAbilityList.end());
	
	this->refreshParticleFx();
}

void HackableObject::registerClippyOnto(std::string identifier, std::function<Clippy*()> clippyFunc)
{
	this->clippyMap[identifier] = clippyFunc;
}

void HackableObject::createHackParticles()
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

HackButton* HackableObject::buildHackButton()
{
	HackButton* instance = HackButton::create();

	instance->setVisible(false);

	instance->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->onHackableClick();
	});

	return instance;
}
