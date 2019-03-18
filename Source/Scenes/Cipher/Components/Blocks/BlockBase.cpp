#include "BlockBase.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Input/ClickableNode.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

BlockBase::BlockBase(ClickableNode* block)
{
	this->block = block;

	this->addChild(this->block);
}

BlockBase::~BlockBase()
{
}

void BlockBase::initializeListeners()
{
	super::initializeListeners();

	this->block->setMouseDragCallback([=](MouseEvents::MouseEventArgs* args)
	{
		this->setPosition(args->mouseCoords);
	});
}
