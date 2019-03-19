#include "BlockBase.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Config.h"

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

		this->block->setMouseReleaseCallback([=](MouseEvents::MouseEventArgs* args)
		{
			if (this->isToolBoxItem)
			{
				if (this->isInGameArea())
				{
					CipherEvents::TriggerRequestToolSpawn(CipherEvents::CipherSpawnArgs([=](){ return this->spawn(); }, args->mouseCoords + this->clickDelta));
				}

				this->setOpacity(0);
				this->label->stopAllActions();
				this->label->setOpacity(0);
				this->runAction(FadeTo::create(0.5f, 255));
				this->setPosition(this->originalPosition);

				MouseEvents::TriggerMouseRefresh(*args);
			}
			else
			{
				if (!this->isInGameArea())
				{
					this->removeConnections();

					// Despawn out-of-bounds nodes
					GameUtils::changeParent(this, nullptr, false);
				}
			}
			
		});
	}

	// Mouse over effects
	if (this->isToolBoxItem)
	{
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

bool BlockBase::isInGameArea()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 center = Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter, visibleSize.height / 2.0f);
	Vec2 thisPosition = this->getPosition();

	if (thisPosition.x > center.x - Config::GameAreaWidth / 2.0f &&
		thisPosition.x < center.x + Config::GameAreaWidth / 2.0f &&
		thisPosition.y > center.y - Config::GameAreaHeight / 2.0f &&
		thisPosition.y < center.y + Config::GameAreaHeight / 2.0f)
	{
		return true;
	}

	return false;
}

void BlockBase::removeConnections()
{
}
