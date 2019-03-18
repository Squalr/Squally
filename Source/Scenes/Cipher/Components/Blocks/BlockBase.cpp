#include "BlockBase.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableNode.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

BlockBase::BlockBase()
{
	this->blockFrameBinary = ClickableNode::create();
	this->blockFrameDecimal = ClickableNode::create();
	this->blockFrameHex = ClickableNode::create();
	this->blockFrameAscii = ClickableNode::create();

	this->addChild(this->blockFrameBinary);
	this->addChild(this->blockFrameDecimal);
	this->addChild(this->blockFrameHex);
	this->addChild(this->blockFrameAscii);
}

BlockBase::~BlockBase()
{
}

void BlockBase::initializeListeners()
{
	super::initializeListeners();
}
