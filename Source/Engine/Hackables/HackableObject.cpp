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

HackableObject::HackableObject(ValueMap* initProperties) : SerializableObject(initProperties)
{
	this->hackableList = std::vector<HackableAttribute*>();
	this->dataList = std::vector<HackableData*>();
	this->codeList = std::vector<HackableCode*>();
	this->hackButton = HackButton::create();
	this->defaultPreview = nullptr;
	
	this->hackButton->setVisible(false);

	this->addChild(this->hackButton);
}

HackableObject::~HackableObject()
{
	if (this->defaultPreview != nullptr)
	{
		this->defaultPreview->release();
	}
}

void HackableObject::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->hackButton->setClickCallback(CC_CALLBACK_1(HackableObject::onHackableClick, this));

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

void HackableObject::onHackerModeEnable()
{
	this->hackButton->setPosition(this->getButtonOffset());

	if (!(this->dataList.empty() && this->codeList.empty()))
	{
		this->hackButton->setVisible(true);
	}
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

HackablePreview* HackableObject::getDefaultPreview()
{
	return this->defaultPreview;
}

void HackableObject::setDefaultPreview(HackablePreview* defaultPreview)
{
	if (this->defaultPreview != nullptr)
	{
		this->defaultPreview->release();
	}

	this->defaultPreview = defaultPreview;
	this->defaultPreview->retain();
}

void HackableObject::registerData(HackableData* hackableData)
{
	this->addChild(hackableData);
	this->hackableList.push_back(hackableData);
	this->dataList.push_back(hackableData);
}

void HackableObject::registerCode(HackableCode* hackableCode)
{
	this->addChild(hackableCode);
	this->hackableList.push_back(hackableCode);
	this->codeList.push_back(hackableCode);
}
