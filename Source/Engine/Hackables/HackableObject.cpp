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

HackableObject::HackableObject(const ValueMap& properties) : SerializableObject(properties)
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

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::HackAppliedEvent, [=](EventCustom* eventCustom)
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

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::HackerModeEnable, [=](EventCustom* eventCustom)
	{
		this->onHackerModeEnable();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::HackerModeDisable, [=](EventCustom* eventCustom)
	{
		this->onHackerModeDisable();
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

void HackableObject::onHackerModeEnable()
{
	this->uiElements->setPosition(this->getButtonOffset());

	if (!(this->dataList.empty() && this->codeList.empty()))
	{
		this->hackButton->setVisible(true);
	}
}

void HackableObject::registerHackables()
{
}

void HackableObject::onHackerModeDisable()
{
	this->hackButton->setVisible(false);
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
	this->removeChild(hackableData);

	this->hackableList.erase(std::remove(this->hackableList.begin(), this->hackableList.end(), hackableData), this->hackableList.end());
	this->dataList.erase(std::remove(this->dataList.begin(), this->dataList.end(), hackableData), this->dataList.end());
}

void HackableObject::registerCode(HackableCode* hackableCode)
{
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
	this->removeChild(hackableCode);

	this->hackableList.erase(std::remove(this->hackableList.begin(), this->hackableList.end(), hackableCode), this->hackableList.end());
	this->codeList.erase(std::remove(this->codeList.begin(), this->codeList.end(), hackableCode), this->codeList.end());
}
