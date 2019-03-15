#include "HackableObject.h"

#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"

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

HackableObject::HackableObject(const ValueMap& initProperties) : SerializableObject(initProperties)
{
	this->hackableList = std::vector<HackableAttribute*>();
	this->dataList = std::vector<HackableData*>();
	this->codeList = std::vector<HackableCode*>();
	this->trackedAttributes = std::vector<HackableAttribute*>();
	this->uiElements = Node::create();
	this->uiElementsBindings = UIBoundObject::create(this->uiElements);
	this->hackButton = HackButton::create();
	this->timeRemainingBar = ProgressBar::create(UIResources::HUD_StatFrame, UIResources::HUD_HackBarFill);

	this->hackButton->setVisible(false);
	this->timeRemainingBar->setVisible(false);

	this->uiElements->addChild(this->hackButton);
	this->uiElements->addChild(this->timeRemainingBar);
	this->addChild(this->uiElements);
	this->addChild(this->uiElementsBindings);
}

HackableObject::~HackableObject()
{
}

void HackableObject::onEnter()
{
	super::onEnter();

	// Move the UI elements to the top-most layer
	ObjectEvents::TriggerMoveObjectToTopLayer(ObjectEvents::RelocateObjectArgs(
		this->uiElementsBindings
	));

	this->registerHackables();
	this->scheduleUpdate();
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

void HackableObject::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->hackButton->setClickCallback(CC_CALLBACK_1(HackableObject::onHackableClick, this));

	this->registerHackables();

	HackableEvents::TriggerRegisterHackable(HackableEvents::HackableObjectRegisterArgs(this));
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

	this->uiElementsBindings->setPosition(this->getButtonOffset());
}

void HackableObject::onHackerModeEnable()
{
	this->uiElementsBindings->setPosition(this->getButtonOffset());

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

void HackableObject::onHackableClick(ClickableNode* hackButton)
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
