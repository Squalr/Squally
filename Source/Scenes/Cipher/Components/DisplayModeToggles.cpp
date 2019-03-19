#include "DisplayModeToggles.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

DisplayModeToggles* DisplayModeToggles::create()
{
	DisplayModeToggles* instance = new DisplayModeToggles();

	instance->autorelease();

	return instance;
}

DisplayModeToggles::DisplayModeToggles()
{
	this->toggleButtonBin = ClickableNode::create(CipherResources::BinaryButton, CipherResources::BinaryButtonSelected);
	this->toggleButtonDec = ClickableNode::create(CipherResources::DecimalButton, CipherResources::DecimalButtonSelected);
	this->toggleButtonHex = ClickableNode::create(CipherResources::HexButton, CipherResources::HexButtonSelected);
	this->toggleButtonAscii = ClickableNode::create(CipherResources::AsciiButton, CipherResources::AsciiButtonSelected);

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
}

void DisplayModeToggles::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->toggleButtonBin->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + -532.0f + 64.0f * 0.0f, visibleSize.height / 2.0f + 416.0f));
	this->toggleButtonDec->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + -532.0f + 64.0f * 1.0f, visibleSize.height / 2.0f + 416.0f));
	this->toggleButtonHex->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + -532.0f + 64.0f * 2.0f, visibleSize.height / 2.0f + 416.0f));
	this->toggleButtonAscii->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + -532.0f + 64.0f * 3.0f, visibleSize.height / 2.0f + 416.0f));
}

void DisplayModeToggles::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void DisplayModeToggles::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}
