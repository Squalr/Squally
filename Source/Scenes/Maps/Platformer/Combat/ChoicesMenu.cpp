#include "ChoicesMenu.h"

#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/UI/Controls/CProgressBar.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const float ChoicesMenu::InnerChoicesRadius = 240.0f;
const float ChoicesMenu::OuterChoicesRadius = 480.0f;

ChoicesMenu* ChoicesMenu::create(std::function<void()> onChoiceMadeCallback)
{
	ChoicesMenu* instance = new ChoicesMenu(onChoiceMadeCallback);

	instance->autorelease();

	return instance;
}

ChoicesMenu::ChoicesMenu(std::function<void()> onChoiceMadeCallback)
{
	this->itemsNode = ClickableNode::create(UIResources::Combat_ItemsCircle, UIResources::Combat_ItemsCircle);
	this->attackNode = ClickableNode::create(UIResources::Combat_AttackCircle, UIResources::Combat_AttackCircle);
	this->defendNode = ClickableNode::create(UIResources::Combat_DefendCircle, UIResources::Combat_DefendCircle);
	this->onChoiceMadeCallback = onChoiceMadeCallback;

	this->itemsNode->addChild(Sprite::create(UIResources::Menus_Icons_Dice));
	this->attackNode->addChild(Sprite::create(UIResources::Menus_Icons_Spear));
	this->defendNode->addChild(Sprite::create(UIResources::Menus_Icons_ShieldBroken));

	this->addChild(this->itemsNode);
	this->addChild(this->attackNode);
	this->addChild(this->defendNode);
}

void ChoicesMenu::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void ChoicesMenu::initializePositions()
{
	super::initializePositions();

	this->itemsNode->setPosition(Vec2(ChoicesMenu::InnerChoicesRadius * std::cos(M_PI / 7), ChoicesMenu::InnerChoicesRadius * std::sin(M_PI / 7)));
	this->attackNode->setPosition(Vec2(ChoicesMenu::InnerChoicesRadius * std::cos(0.0f), ChoicesMenu::InnerChoicesRadius * std::sin(0.0f)));
	this->defendNode->setPosition(Vec2(ChoicesMenu::InnerChoicesRadius * std::cos(-M_PI / 7), ChoicesMenu::InnerChoicesRadius * std::sin(-M_PI / 7)));
}

void ChoicesMenu::initializeListeners()
{
	super::initializeListeners();

	this->itemsNode->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*) { this->onItemsClick(); });
	this->attackNode->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*) { this->onAttackClick(); });
	this->defendNode->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*) { this->onDefendClick(); });
}

void ChoicesMenu::update(float dt)
{
	super::update(dt);
}

void ChoicesMenu::onItemsClick()
{
	if (this->onChoiceMadeCallback != nullptr)
	{
		this->onChoiceMadeCallback();
	}
}

void ChoicesMenu::onAttackClick()
{
	if (this->onChoiceMadeCallback != nullptr)
	{
		this->onChoiceMadeCallback();
	}
}

void ChoicesMenu::onDefendClick()
{
	if (this->onChoiceMadeCallback != nullptr)
	{
		this->onChoiceMadeCallback();
	}
}
