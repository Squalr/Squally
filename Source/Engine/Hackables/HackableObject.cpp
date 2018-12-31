#include "HackableObject.h"

#include "base/CCEventListenerCustom.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Hackables/HackButton.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Events/HackableEvents.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

HackableObject::HackableObject(ValueMap* initProperties) : SerializableObject(initProperties)
{
	this->dataList = std::vector<HackableData*>();
	this->codeList = std::vector<HackableCode*>();
	this->hackButton = HackButton::create();
	
	this->hackButton->setVisible(false);

	this->addChild(this->hackButton);
}

HackableObject::~HackableObject()
{
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

void HackableObject::onHackerModeEnable()
{
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

void HackableObject::onHackableClick(MenuSprite* hackButton)
{
	Vec2 screenPosition = GameUtils::getSceneBounds(this).origin;

	HackableEvents::TriggerEditHackable(HackableEvents::HackableObjectEditArgs(this, screenPosition));
}

void HackableObject::registerData(HackableData* hackableData)
{
	hackableData->retain();
	this->dataList.push_back(hackableData);
}

void HackableObject::registerCode(HackableCode* hackableCode)
{
	hackableCode->retain();
	this->codeList.push_back(hackableCode);
}
