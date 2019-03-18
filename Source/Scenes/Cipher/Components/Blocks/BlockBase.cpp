#include "BlockBase.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

BlockBase::BlockBase(ClickableNode* block, LocalizedString* label)
{
	this->block = block;
	this->label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, label);

	this->label->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->block);
	this->addChild(this->label);
}

BlockBase::~BlockBase()
{
}

void BlockBase::initializePositions()
{
	super::initializePositions();

	this->label->setPosition(Vec2(0.0f, 4.0f));
}

void BlockBase::initializeListeners()
{
	super::initializeListeners();

	this->block->setMouseDragCallback([=](MouseEvents::MouseEventArgs* args)
	{
		this->setPosition(args->mouseCoords);
	});
}
