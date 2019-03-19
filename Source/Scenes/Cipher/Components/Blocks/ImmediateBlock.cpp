#include "ImmediateBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/Immediate.h"

using namespace cocos2d;

ImmediateBlock* ImmediateBlock::create(bool isToolBoxItem, bool isStaticObject)
{
	ImmediateBlock* instance = new ImmediateBlock(isToolBoxItem, isStaticObject);

	instance->autorelease();

	return instance;
}

ImmediateBlock::ImmediateBlock(bool isToolBoxItem, bool isStaticObject) : super(isToolBoxItem, ClickableNode::create(CipherResources::BlockDecLong, CipherResources::BlockDecLong), CipherResources::Icons_Immediate, Strings::Cipher_Operations_Immediate::create())
{
	this->isStaticObject = isStaticObject;
}

ImmediateBlock::~ImmediateBlock()
{
}

void ImmediateBlock::onEnter()
{
	super::onEnter();
}

void ImmediateBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

BlockBase* ImmediateBlock::spawn()
{
	return ImmediateBlock::create();
}
