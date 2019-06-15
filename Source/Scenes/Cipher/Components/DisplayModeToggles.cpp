#include "DisplayModeToggles.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/UI/Controls/RadioButton.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

const int DisplayModeToggles::GroupIdDisplayModeToggles = 985703765; // RNG based to avoid conflicts

DisplayModeToggles* DisplayModeToggles::create(bool inAsciiMenu)
{
	DisplayModeToggles* instance = new DisplayModeToggles(inAsciiMenu);

	instance->autorelease();

	return instance;
}

DisplayModeToggles::DisplayModeToggles(bool inAsciiMenu)
{
	this->inAsciiMenu = inAsciiMenu;
	this->toggleButtonBin = RadioButton::create(
		ClickableNode::create(CipherResources::Buttons_BinaryButtonActive, CipherResources::Buttons_BinaryButtonActive),
		ClickableNode::create(CipherResources::Buttons_BinaryButton, CipherResources::Buttons_BinaryButtonSelected),
		DisplayModeToggles::GroupIdDisplayModeToggles
	);
	this->toggleButtonDec = RadioButton::create(
		ClickableNode::create(CipherResources::Buttons_DecimalButtonActive, CipherResources::Buttons_DecimalButtonActive),
		ClickableNode::create(CipherResources::Buttons_DecimalButton, CipherResources::Buttons_DecimalButtonSelected),
		DisplayModeToggles::GroupIdDisplayModeToggles
	);
	this->toggleButtonHex = RadioButton::create(
		ClickableNode::create(CipherResources::Buttons_HexButtonActive, CipherResources::Buttons_HexButtonActive),
		ClickableNode::create(CipherResources::Buttons_HexButton, CipherResources::Buttons_HexButtonSelected),
		DisplayModeToggles::GroupIdDisplayModeToggles
	);
	this->toggleButtonAscii = RadioButton::create(
		ClickableNode::create(CipherResources::Buttons_AsciiButtonActive, CipherResources::Buttons_AsciiButtonActive),
		ClickableNode::create(CipherResources::Buttons_AsciiButton, CipherResources::Buttons_AsciiButtonSelected),
		DisplayModeToggles::GroupIdDisplayModeToggles
	);

	this->addChild(this->toggleButtonBin);
	this->addChild(this->toggleButtonDec);
	this->addChild(this->toggleButtonHex);
	this->addChild(this->toggleButtonAscii);
}

DisplayModeToggles::~DisplayModeToggles()
{
}

void DisplayModeToggles::onEnter()
{
	super::onEnter();

	this->toggleButtonAscii->check();
}

void DisplayModeToggles::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (this->inAsciiMenu)
	{
		this->toggleButtonDec->setPosition(Vec2(visibleSize.width / 2.0f - 512.0f + 64.0f * 0.0f, visibleSize.height / 2.0f - 356.0f));
		this->toggleButtonHex->setPosition(Vec2(visibleSize.width / 2.0f - 512.0f + 64.0f * 1.0f, visibleSize.height / 2.0f - 356.0f));
		this->toggleButtonBin->setPosition(Vec2(visibleSize.width / 2.0f - 512.0f + 64.0f * 2.0f, visibleSize.height / 2.0f - 356.0f));
		this->toggleButtonAscii->setPosition(Vec2(visibleSize.width / 2.0f - 512.0f + 64.0f * 3.0f, visibleSize.height / 2.0f - 356.0f));
	}
	else
	{
		this->toggleButtonDec->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + -532.0f + 64.0f * 0.0f, visibleSize.height / 2.0f + 416.0f));
		this->toggleButtonHex->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + -532.0f + 64.0f * 1.0f, visibleSize.height / 2.0f + 416.0f));
		this->toggleButtonBin->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + -532.0f + 64.0f * 2.0f, visibleSize.height / 2.0f + 416.0f));
		this->toggleButtonAscii->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + -532.0f + 64.0f * 3.0f, visibleSize.height / 2.0f + 416.0f));
	}
}

void DisplayModeToggles::initializeListeners()
{
	super::initializeListeners();

	this->toggleButtonBin->setCheckCallback([=](RadioButton*)
	{
		CipherEvents::TriggerChangeDisplayDataType(CipherEvents::CipherChangeDisplayDataTypeArgs(CipherEvents::DisplayDataType::Bin));
	});
	this->toggleButtonDec->setCheckCallback([=](RadioButton*)
	{
		CipherEvents::TriggerChangeDisplayDataType(CipherEvents::CipherChangeDisplayDataTypeArgs(CipherEvents::DisplayDataType::Dec));
	});
	this->toggleButtonHex->setCheckCallback([=](RadioButton*)
	{
		CipherEvents::TriggerChangeDisplayDataType(CipherEvents::CipherChangeDisplayDataTypeArgs(CipherEvents::DisplayDataType::Hex));
	});
	this->toggleButtonAscii->setCheckCallback([=](RadioButton*)
	{
		CipherEvents::TriggerChangeDisplayDataType(CipherEvents::CipherChangeDisplayDataTypeArgs(CipherEvents::DisplayDataType::Ascii));
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_1 }, [=](InputEvents::InputArgs* args)
	{
		this->toggleButtonDec->check();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_2 }, [=](InputEvents::InputArgs* args)
	{
		this->toggleButtonHex->check();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_3 }, [=](InputEvents::InputArgs* args)
	{
		this->toggleButtonBin->check();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_4 }, [=](InputEvents::InputArgs* args)
	{
		this->toggleButtonAscii->check();
	});
}

void DisplayModeToggles::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void DisplayModeToggles::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}
