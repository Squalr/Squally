#include "ShrBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/SHR.h"

using namespace cocos2d;

ShrBlock* ShrBlock::create()
{
	ShrBlock* instance = new ShrBlock();

	instance->autorelease();

	return instance;
}

ShrBlock::ShrBlock() : super(ClickableNode::create(CipherResources::BlockBin, CipherResources::BlockBin), CipherResources::Icons_ShiftRight, Strings::Cipher_Operations_SHR::create())
{
}

ShrBlock::~ShrBlock()
{
}

void ShrBlock::onEnter()
{
	super::onEnter();
}

void ShrBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}
