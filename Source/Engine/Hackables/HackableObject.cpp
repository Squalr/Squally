#include "HackableObject.h"

#include "base/CCEventListenerCustom.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Hackables/HackButton.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Events/HackableEvents.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

HackableObject::HackableObject(const ValueMap& initProperties) : SerializableObject(initProperties)
{
	this->hackableList = std::vector<HackableAttribute*>();
	this->dataList = std::vector<HackableData*>();
	this->codeList = std::vector<HackableCode*>();
	this->uiElements = Node::create();
	this->hackButton = HackButton::create();
	
	this->hackButton->setVisible(false);

	this->uiElements->addChild(this->hackButton);
	this->addChild(this->uiElements);
}

HackableObject::~HackableObject()
{
}

void HackableObject::onEnter()
{
	super::onEnter();

	this->registerHackables();
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

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::HackerModeEnable, [=](EventCustom* args)
	{
		this->onHackerModeEnable();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::HackerModeDisable, [=](EventCustom* args)
	{
		this->onHackerModeDisable();
	}));
}

void HackableObject::initializePositions()
{
	super::initializePositions();

	this->hackButton->setPosition(this->getButtonOffset());
}

void HackableObject::addChild(Node* child)
{
	super::addChild(child);

	// Magic trick to resort-z index
	GameUtils::changeParent(this->uiElements, this, true);
}

void HackableObject::onHackerModeEnable()
{
	this->hackButton->setPosition(this->getButtonOffset());

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
		if ((*it)->getDataPointer() == hackableData->getDataPointer())
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
		if ((*it)->getCodePointer() == hackableCode->getCodePointer())
		{
			return;
		}
	}

	this->addChild(hackableCode);
	this->hackableList.push_back(hackableCode);
	this->codeList.push_back(hackableCode);
}
