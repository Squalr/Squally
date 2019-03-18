#include "ToolBox.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/Components/Blocks/XorBlock.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

ToolBox* ToolBox::create()
{
	ToolBox* instance = new ToolBox();

	instance->autorelease();

	return instance;
}

ToolBox::ToolBox()
{
	this->xorBlock = XorBlock::create();

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
}

void ToolBox::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void ToolBox::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}
