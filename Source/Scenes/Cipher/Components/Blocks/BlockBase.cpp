#include "BlockBase.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Input/ClickableNode.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

BlockBase::BlockBase()
{
	this->blockFrameBinary = ClickableNode::create(CipherResources::BinaryBlock, CipherResources::BinaryBlock);
	this->blockFrameDecimal = ClickableNode::create(CipherResources::DecimalBlock, CipherResources::DecimalBlock);
	this->blockFrameHex = ClickableNode::create(CipherResources::HexBlock, CipherResources::HexBlock);
	this->blockFrameAscii = ClickableNode::create(CipherResources::AsciiBlock, CipherResources::AsciiBlock);

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


	this->blockFrameAscii->setMouseDragCallback([=](MouseEvents::MouseEventArgs* args)
	{

	});
}
