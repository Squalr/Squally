#include "BlockBase.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Events/CipherEvents.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

BlockBase::BlockBase(bool isToolBoxItem, ClickableNode* block, std::string iconResource, LocalizedString* label)
{
	this->block = block;
	this->icon = Sprite::create(iconResource);
	this->label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, label);
	this->isToolBoxItem = isToolBoxItem;
	this->isStaticObject = false;
	this->originalPosition = Vec2::ZERO;
	this->clickDelta = Vec2::ZERO;

	this->label->enableOutline(Color4B::BLACK, 2);
	this->label->setOpacity(0);

	this->addChild(this->block);
	this->addChild(this->icon);
	this->addChild(this->label);
}

BlockBase::~BlockBase()
{
}

void BlockBase::initializePositions()
{
	super::initializePositions();

	this->icon->setPosition(Vec2(0.0f, 4.0f));
	this->label->setPosition(Vec2(0.0f, 48.0f));
}

void BlockBase::initializeListeners()
{
	super::initializeListeners();

	if (this->isStaticObject)
	{
		this->block->disableInteraction();
	}

	// Mouse dragging effects
	if (!this->isStaticObject)
	{
		this->block->setMousePressCallback([=](MouseEvents::MouseEventArgs* args)
		{
			this->originalPosition = this->getPosition();
			this->clickDelta = this->originalPosition - args->mouseCoords;
		});

		this->block->setMouseDragCallback([=](MouseEvents::MouseEventArgs* args)
		{
			this->setPosition(args->mouseCoords + this->clickDelta);
		});
	}

	// Spawn + Mouse over effects
	if (this->isToolBoxItem)
	{
		this->block->setMouseReleaseCallback([=](MouseEvents::MouseEventArgs* args)
		{
			this->setOpacity(0);
			this->label->stopAllActions();
			this->label->setOpacity(0);

			this->runAction(FadeTo::create(0.5f, 255));
			this->setPosition(this->originalPosition);

			MouseEvents::TriggerMouseRefresh(*args);
			
			CipherEvents::TriggerRequestToolSpawn(CipherEvents::CipherSpawnArgs([=](){ return this->spawn(); }, args->mouseCoords + this->clickDelta));
		});

		this->block->setMouseInCallback([=](MouseEvents::MouseEventArgs* args)
		{
			this->label->stopAllActions();
			this->label->runAction(FadeTo::create(0.25f, 255));
		});

		this->block->setMouseOutCallback([=](MouseEvents::MouseEventArgs* args)
		{
			this->label->stopAllActions();
			this->label->runAction(FadeTo::create(0.25f, 0));
		});
	}
}
