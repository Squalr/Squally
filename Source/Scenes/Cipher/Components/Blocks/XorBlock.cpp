#include "XorBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

XorBlock* XorBlock::create()
{
	XorBlock* instance = new XorBlock();

	instance->autorelease();

	return instance;
}

XorBlock::XorBlock()
{
}

XorBlock::~XorBlock()
{
}

void XorBlock::onEnter()
{
	super::onEnter();
}

void XorBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}
