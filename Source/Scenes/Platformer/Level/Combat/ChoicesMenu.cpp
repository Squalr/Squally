#include "ChoicesMenu.h"

#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

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
	this->itemListNode = Node::create();
	this->defendListNode = Node::create();
	this->attackListNodes = std::vector<ClickableTextNode*>();
	this->itemListNodes = std::vector<ClickableTextNode*>();

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
	this->addChild(this->attackListNode);
	this->addChild(this->itemListNode);
	this->addChild(this->defendListNode);
}

void ChoicesMenu::onEnter()
{
	super::onEnter();

	this->setVisible(false);
	this->attackListNode->setVisible(false);
	this->itemListNode->setVisible(false);

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

		if (combatArgs != nullptr)
		{
			switch (combatArgs->currentMenu)
			{
				case CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect:
				{
					this->attackListNode->setVisible(false);
					this->defendListNode->setVisible(false);
					this->itemListNode->setVisible(false);
					this->toggleInnerText(true);
					this->toggleOuterText(false);

					this->setSelectedEntry(combatArgs->entry);
					this->setVisible(true);

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::AttackSelect:
				{
					this->attackListNode->setVisible(true);
					this->defendListNode->setVisible(false);
					this->itemListNode->setVisible(false);
					this->toggleInnerText(false);
					this->toggleOuterText(true);

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ItemSelect:
				{
					this->attackListNode->setVisible(false);
					this->defendListNode->setVisible(false);
					this->itemListNode->setVisible(true);
					this->toggleInnerText(false);
					this->toggleOuterText(true);

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::DefendSelect:
				{
					this->attackListNode->setVisible(false);
					this->defendListNode->setVisible(true);
					this->itemListNode->setVisible(false);
					this->toggleInnerText(false);
					this->toggleOuterText(true);

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget:
				{
					this->toggleInnerText(false);
					this->toggleOuterText(false);

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::Closed:
				{
					this->attackListNode->setVisible(false);
					this->defendListNode->setVisible(false);
					this->itemListNode->setVisible(false);
					this->setVisible(false);

					break;
				}
				default:
				{
					break;
				}
			}
		}
	}));

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
	CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ItemSelect, this->selectedEntry));
}

void ChoicesMenu::onAttackClick()
{
	CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::AttackSelect, this->selectedEntry));
}

void ChoicesMenu::onDefendClick()
{
	CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::DefendSelect, this->selectedEntry));
}

void ChoicesMenu::toggleInnerText(bool isVisible)
{
	this->itemsNode->setTextVisible(isVisible);
	this->attackNode->setTextVisible(isVisible);
	this->defendNode->setTextVisible(isVisible);

	this->itemsNode->setOpacity(isVisible ? 255 : 127);
	this->attackNode->setOpacity(isVisible ? 255 : 127);
	this->defendNode->setOpacity(isVisible ? 255 : 127);
}

void ChoicesMenu::toggleOuterText(bool isVisible)
{
	for (auto it = this->attackListNodes.begin(); it != this->attackListNodes.end(); it++)
	{
		(*it)->setTextVisible(isVisible);
		(*it)->setOpacity(isVisible ? 255 : 127);
	}

	for (auto it = this->itemListNodes.begin(); it != this->itemListNodes.end(); it++)
	{
		(*it)->setTextVisible(isVisible);
		(*it)->setOpacity(isVisible ? 255 : 127);
	}
}

void ChoicesMenu::setSelectedEntry(TimelineEntry* selectedEntry)
{
	this->selectedEntry = selectedEntry;

	this->buildAttackList();
	this->buildItemList();
}

void ChoicesMenu::buildAttackList()
{
	const float AngleDelta = M_PI / 6.0f;
	float currentAngle = 0.0f;

	this->attackListNodes.clear();
	this->attackListNode->removeAllChildren();

	if (this->selectedEntry != nullptr)
	{
		PlatformerEntity* entity = this->selectedEntry->getEntity();

		if (entity != nullptr)
		{
			std::vector<PlatformerAttack*> attacks = entity->getAttacks();

			for (auto it = attacks.begin(); it != attacks.end(); it++)
			{
				PlatformerAttack* attack = *it;
				LocalizedLabel* attackLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, attack->getString());
				LocalizedLabel* attackLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, attack->getString());

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

				currentAngle = (currentAngle <= 0.0f ? 1.0f : -1.0f) * (std::abs(currentAngle) + (currentAngle <= 0.0f ? AngleDelta : 0.0f));

				this->attackListNodes.push_back(node);
				this->attackListNode->addChild(node);
			}
		}
	}
}

void ChoicesMenu::buildItemList()
{
	const float AngleDelta = M_PI / 6.0f;
	float currentAngle = 0.0f;

	this->itemListNodes.clear();
	this->itemListNode->removeAllChildren();

	if (this->selectedEntry != nullptr)
	{
		PlatformerEntity* entity = this->selectedEntry->getEntity();

		if (entity != nullptr)
		{
			Inventory* inventory = entity->getInventory();
			
			if (inventory != nullptr)
			{
				std::vector<Consumable*> items = inventory->getItemsOfType<Consumable>();

				for (auto it = items.begin(); it != items.end(); it++)
				{
					Consumable* item = *it;
					LocalizedLabel* itemLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, item->getString());
					LocalizedLabel* itemLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, item->getString());

					itemLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
					itemLabelSelected->setAnchorPoint(Vec2(0.0f, 0.5f));
					itemLabel->enableOutline(Color4B::BLACK, 2);
					itemLabelSelected->enableOutline(Color4B::BLACK, 2);
					itemLabelSelected->setTextColor(Color4B::YELLOW);

					ClickableTextNode* node = ClickableTextNode::create(itemLabel, itemLabelSelected, UIResources::Combat_ItemsCircle, UIResources::Combat_ItemsCircle);

					node->setTextOffset(Vec2(48.0f, 0.0f));
					node->setPosition(Vec2(ChoicesMenu::OuterChoicesRadius * std::cos(currentAngle), ChoicesMenu::OuterChoicesRadius * std::sin(currentAngle)));
					node->addChild(Sprite::create(item->getIconResource()));

					node->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*)
					{
						this->selectedEntry->stageCast(item->createAssociatedAttack());

						switch (item->getConsumableType())
						{
							default:
							case Consumable::ConsumableType::Buff:
							{
								CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget, this->selectedEntry));
								break;
							}
							case Consumable::ConsumableType::Debuff:
							{
								CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget, this->selectedEntry));
								break;
							}
							case Consumable::ConsumableType::Either:
							{
								CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget, this->selectedEntry));
								break;
							}
						}
					});

					currentAngle = (currentAngle <= 0.0f ? 1.0f : -1.0f) * (std::abs(currentAngle) + (currentAngle <= 0.0f ? AngleDelta : 0.0f));

					this->itemListNodes.push_back(node);
					this->itemListNode->addChild(node);
				}
			}
		}

	}
}
