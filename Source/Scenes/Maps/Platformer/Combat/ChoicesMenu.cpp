#include "ChoicesMenu.h"

#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/CProgressBar.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Attacks/PlatformerAttack.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Maps/Platformer/Combat/TimelineEntry.h"

#include "Resources/UIResources.h"

#include "Strings/Combat/Attack.h"
#include "Strings/Combat/Defend.h"
#include "Strings/Combat/Items.h"

using namespace cocos2d;

const float ChoicesMenu::InnerChoicesRadius = 240.0f;
const float ChoicesMenu::OuterChoicesRadius = 384.0f;

ChoicesMenu* ChoicesMenu::create()
{
	ChoicesMenu* instance = new ChoicesMenu();

	instance->autorelease();

	return instance;
}

ChoicesMenu::ChoicesMenu()
{
	this->selectedEntry = nullptr;

	LocalizedLabel* itemsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Combat_Items::create());
	LocalizedLabel* attackLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Combat_Attack::create());
	LocalizedLabel* defendLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Combat_Defend::create());
	LocalizedLabel* itemsLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Combat_Items::create());
	LocalizedLabel* attackLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Combat_Attack::create());
	LocalizedLabel* defendLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Combat_Defend::create());

	this->itemsNode = ClickableTextNode::create(itemsLabel, itemsLabelSelected, UIResources::Combat_ItemsCircle, UIResources::Combat_ItemsCircle);
	this->attackNode = ClickableTextNode::create(attackLabel, attackLabelSelected, UIResources::Combat_AttackCircle, UIResources::Combat_AttackCircle);
	this->defendNode = ClickableTextNode::create(defendLabel, defendLabelSelected, UIResources::Combat_DefendCircle, UIResources::Combat_DefendCircle);
	this->attackListNode = Node::create();

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

	this->setVisible(false);
	this->attackListNode->setVisible(false);

	this->addChild(this->itemsNode);
	this->addChild(this->attackNode);
	this->addChild(this->defendNode);
	this->addChild(this->attackListNode);
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

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventChangeMenuState, [=](EventCustom* args)
	{
		CombatEvents::MenuStateArgs* combatArgs = static_cast<CombatEvents::MenuStateArgs*>(args->getUserData());

		if (combatArgs != nullptr && combatArgs->entry != nullptr)
		{
			switch (combatArgs->currentMenu)
			{
				case CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect:
				{
					this->setSelectedEntry(combatArgs->entry);
					this->open();

					break;
				}
				default:
				{
					break;
				}
			}
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventUserActionMade, [=](EventCustom* args)
	{
		this->onUserActionMade();
	}));

	this->itemsNode->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*) { this->onItemsClick(); });
	this->attackNode->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*) { this->onAttackClick(); });
	this->defendNode->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*) { this->onDefendClick(); });
}

void ChoicesMenu::update(float dt)
{
	super::update(dt);
}

void ChoicesMenu::open()
{
	this->setVisible(true);
	this->toggleInnerText(true);
}

void ChoicesMenu::onUserActionMade()
{
	this->setVisible(false);
	this->attackListNode->setVisible(false);
}

void ChoicesMenu::onItemsClick()
{
	CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ItemSelect, this->selectedEntry));
	this->toggleInnerText(false);
}

void ChoicesMenu::onAttackClick()
{
	CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::AttackSelect, this->selectedEntry));

	this->attackListNode->setVisible(true);
	this->toggleInnerText(false);
}

void ChoicesMenu::onDefendClick()
{
	CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::DefendSelect, this->selectedEntry));

	this->toggleInnerText(false);
}

void ChoicesMenu::toggleInnerText(bool isVisible)
{
	this->itemsNode->setTextVisible(isVisible);
	this->attackNode->setTextVisible(isVisible);
	this->defendNode->setTextVisible(isVisible);

	if (isVisible)
	{
		this->itemsNode->setOpacity(255);
		this->attackNode->setOpacity(255);
		this->defendNode->setOpacity(255);
	}
	else
	{
		this->itemsNode->setOpacity(127);
		this->attackNode->setOpacity(127);
		this->defendNode->setOpacity(127);
	}
}

void ChoicesMenu::setSelectedEntry(TimelineEntry* selectedEntry)
{
	const float AngleDelta = M_PI / 6.0f;
	float currentAngle = 0.0f;

	this->selectedEntry = selectedEntry;

	PlatformerEntity* entity = this->selectedEntry->getEntity();

	this->attackListNode->removeAllChildren();

	if (entity != nullptr)
	{
		std::vector<PlatformerAttack*> attacks = entity->getAttacks();

		for (auto it = attacks.begin(); it != attacks.end(); it++)
		{
			PlatformerAttack* attack = *it;
			LocalizedLabel* attackLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, (*it)->getString());
			LocalizedLabel* attackLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, (*it)->getString());

			attackLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
			attackLabelSelected->setAnchorPoint(Vec2(0.0f, 0.5f));
			attackLabel->enableOutline(Color4B::BLACK, 2);
			attackLabelSelected->enableOutline(Color4B::BLACK, 2);
			attackLabelSelected->setTextColor(Color4B::YELLOW);

			ClickableTextNode* node = ClickableTextNode::create(attackLabel, attackLabelSelected, UIResources::Combat_AttackCircle, UIResources::Combat_AttackCircle);

			node->setTextOffset(Vec2(48.0f, 0.0f));
			node->setPosition(Vec2(ChoicesMenu::OuterChoicesRadius * std::cos(currentAngle), ChoicesMenu::OuterChoicesRadius * std::sin(currentAngle)));
			node->addChild(Sprite::create(attack->getIconResource()));

			node->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*)
			{
				this->selectedEntry->stageCast(attack);

				CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget, this->selectedEntry));
			});

			currentAngle = currentAngle >= 0.0f ? (currentAngle * -1.0f + AngleDelta) : (currentAngle * -1.0f);

			this->attackListNode->addChild(node);
		}
	}
}
