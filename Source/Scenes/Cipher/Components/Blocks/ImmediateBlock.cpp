#include "ImmediateBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/Immediate.h"

using namespace cocos2d;

ImmediateBlock* ImmediateBlock::create()
{
	ImmediateBlock* instance = new ImmediateBlock();

	instance->autorelease();

	return instance;
}

ImmediateBlock::ImmediateBlock() : super(ClickableNode::create(CipherResources::BlockDecLong, CipherResources::BlockDecLong), CipherResources::Icons_Immediate, Strings::Cipher_Operations_Immediate::create())
{
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
