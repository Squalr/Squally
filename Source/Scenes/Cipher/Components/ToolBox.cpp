#include "ToolBox.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/Components/Blocks/XorBlock.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Tools.h"

using namespace cocos2d;

ToolBox* ToolBox::create()
{
	ToolBox* instance = new ToolBox();

	instance->autorelease();

	return instance;
}

ToolBox::ToolBox()
{
	this->cipherToolsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Cipher_Tools::create());
	this->cipherToolsLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);
	this->xorBlock = XorBlock::create();
	
	this->addChild(this->cipherToolsLabel);
	this->addChild(this->xorBlock);
}

ToolBox::~ToolBox()
{
}

void ToolBox::onEnter()
{
	super::onEnter();
}

void ToolBox::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cipherToolsLabel->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter, visibleSize.height / 2.0f + 450.0f));
	this->xorBlock->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter, visibleSize.height / 2.0f + 128.0f));
}

void ToolBox::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void ToolBox::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}
