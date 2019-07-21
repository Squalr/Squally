#include "HackableObject.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Hackables/HackButton.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HackableObject::MapKeyShowClippy = "show-clippy";

HackableObject::HackableObject(const ValueMap& properties) : GameObject(properties)
{
	this->hackableList = std::vector<HackableAttribute*>();
	this->dataList = std::vector<HackableData*>();
	this->codeList = std::vector<HackableCode*>();
	this->trackedAttributes = std::vector<HackableAttribute*>();
	this->uiElements = Node::create();
	this->hackButton = HackButton::create();
	this->timeRemainingBar = ProgressBar::create(UIResources::HUD_StatFrame, UIResources::HUD_HackBarFill);
	this->showClippy = GameUtils::getKeyOrDefault(this->properties, HackableObject::MapKeyShowClippy, Value(false)).asBool();

	this->hackButton->setVisible(false);
	this->timeRemainingBar->setVisible(false);

	this->uiElements->addChild(this->hackButton);
	this->uiElements->addChild(this->timeRemainingBar);
	this->addChild(this->uiElements);
}

HackableObject::~HackableObject()
{
	ObjectEvents::TriggerUnbindObject(ObjectEvents::RelocateObjectArgs(this->uiElements));
}

void HackableObject::onEnter()
{
	super::onEnter();

	// Move the UI elements to the top-most layer
	ObjectEvents::TriggerMoveObjectToTopLayer(ObjectEvents::RelocateObjectArgs(this->uiElements));

	this->registerHackables();
	this->scheduleUpdate();
}

void HackableObject::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->hackButton->setMouseClickCallback(CC_CALLBACK_0(HackableObject::onHackableClick, this));

	this->registerHackables();

	HackableEvents::TriggerRegisterHackable(HackableEvents::HackableObjectRegisterArgs(this));
}

void HackableObject::onExit()
{
	super::onExit();

	ObjectEvents::TriggerUnbindObject(ObjectEvents::RelocateObjectArgs(this->uiElements));
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
}

void HackableObject::initializePositions()
{
	super::initializePositions();

	this->uiElements->setPosition(this->getButtonOffset());
}

void HackableObject::update(float dt)
{
	super::update(dt);
	
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

void HackableObject::onHackerModeEnable(int eq)
{
	super::onHackerModeEnable(eq);

	this->uiElements->setPosition(this->getButtonOffset());

	for (auto it = this->hackableList.begin(); it != this->hackableList.end(); it++)
	{
		if ((*it)->getRequiredEq() > eq)
		{
			return;
		}
	}

	if (!this->hackableList.empty())
	{
		this->hackButton->setVisible(true);
	}
}

void HackableObject::onHackerModeDisable()
{
	super::onHackerModeDisable();

	this->hackButton->setVisible(false);
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
	HackableEvents::TriggerOpenHackable(HackableEvents::HackableObjectOpenArgs(this));
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

	this->addChild(hackableData);
	this->hackableList.push_back(hackableData);
	this->dataList.push_back(hackableData);
}

void HackableObject::unregisterData(HackableData* hackableData)
{
	if (hackableData == nullptr)
	{
		return;
	}

	this->removeChild(hackableData);

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

	this->addChild(hackableCode);
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

		this->removeChild(hackableCode);
	}
}
