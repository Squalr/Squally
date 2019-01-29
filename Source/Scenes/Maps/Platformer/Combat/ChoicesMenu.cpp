#include "ChoicesMenu.h"

#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/CProgressBar.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"

#include "Resources/UIResources.h"

#include "Strings/Combat/Attack.h"
#include "Strings/Combat/Defend.h"
#include "Strings/Combat/Items.h"

using namespace cocos2d;

const float ChoicesMenu::InnerChoicesRadius = 240.0f;
const float ChoicesMenu::OuterChoicesRadius = 480.0f;

ChoicesMenu* ChoicesMenu::create()
{
	ChoicesMenu* instance = new ChoicesMenu();

	instance->autorelease();

	return instance;
}

ChoicesMenu::ChoicesMenu()
{
	LocalizedLabel* itemsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Combat_Items::create());
	LocalizedLabel* attackLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Combat_Attack::create());
	LocalizedLabel* defendLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Combat_Defend::create());
	LocalizedLabel* itemsLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Combat_Items::create());
	LocalizedLabel* attackLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Combat_Attack::create());
	LocalizedLabel* defendLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Combat_Defend::create());

	this->itemsNode = ClickableTextNode::create(itemsLabel, itemsLabelSelected, UIResources::Combat_ItemsCircle, UIResources::Combat_ItemsCircle);
	this->attackNode = ClickableTextNode::create(attackLabel, attackLabelSelected, UIResources::Combat_AttackCircle, UIResources::Combat_AttackCircle);
	this->defendNode = ClickableTextNode::create(defendLabel, defendLabelSelected, UIResources::Combat_DefendCircle, UIResources::Combat_DefendCircle);

	itemsLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	attackLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	defendLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	itemsLabelSelected->setAnchorPoint(Vec2(0.0f, 0.5f));
	attackLabelSelected->setAnchorPoint(Vec2(0.0f, 0.5f));
	defendLabelSelected->setAnchorPoint(Vec2(0.0f, 0.5f));
	itemsLabel->enableOutline(Color4B::BLACK, 2);
	attackLabel->enableOutline(Color4B::BLACK, 2);
	defendLabel->enableOutline(Color4B::BLACK, 2);
	itemsLabelSelected->enableOutline(Color4B::BLACK, 2);
	attackLabelSelected->enableOutline(Color4B::BLACK, 2);
	defendLabelSelected->enableOutline(Color4B::BLACK, 2);
	itemsLabelSelected->setTextColor(Color4B::YELLOW);
	attackLabelSelected->setTextColor(Color4B::YELLOW);
	defendLabelSelected->setTextColor(Color4B::YELLOW);

	this->itemsNode->setTextOffset(Vec2(48.0f, 0.0f));
	this->attackNode->setTextOffset(Vec2(48.0f, 0.0f));
	this->defendNode->setTextOffset(Vec2(48.0f, 0.0f));

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

	const float AngleDelta = M_PI / 6.0f;

	this->itemsNode->setPosition(Vec2(ChoicesMenu::InnerChoicesRadius * std::cos(AngleDelta), ChoicesMenu::InnerChoicesRadius * std::sin(AngleDelta)));
	this->attackNode->setPosition(Vec2(ChoicesMenu::InnerChoicesRadius * std::cos(0.0f), ChoicesMenu::InnerChoicesRadius * std::sin(0.0f)));
	this->defendNode->setPosition(Vec2(ChoicesMenu::InnerChoicesRadius * std::cos(-AngleDelta), ChoicesMenu::InnerChoicesRadius * std::sin(-AngleDelta)));
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
	CombatEvents::TriggerItemSelected();

	// TEMP:
	CombatEvents::TriggerUserActionMade();
}

void ChoicesMenu::onAttackClick()
{
	CombatEvents::TriggerAttackSelected();

	// TEMP:
	CombatEvents::TriggerUserActionMade();
}

void ChoicesMenu::onDefendClick()
{
	CombatEvents::TriggerDefendSelected();

	// TEMP:
	CombatEvents::TriggerUserActionMade();
}
