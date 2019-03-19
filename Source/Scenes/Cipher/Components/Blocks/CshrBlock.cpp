#include "CshrBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/CSHR.h"

using namespace cocos2d;

CshrBlock* CshrBlock::create(bool isToolBoxItem)
{
	CshrBlock* instance = new CshrBlock(isToolBoxItem);

	instance->autorelease();

	return instance;
}

CshrBlock::CshrBlock(bool isToolBoxItem) : super(isToolBoxItem, ClickableNode::create(CipherResources::BlockBin, CipherResources::BlockBin), CipherResources::Icons_CircularShiftRight, Strings::Cipher_Operations_CSHR::create())
{
}

CshrBlock::~CshrBlock()
{
}

void CshrBlock::onEnter()
{
	super::onEnter();
}

void CshrBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

BlockBase* CshrBlock::spawn()
{
	return CshrBlock::create();
}
