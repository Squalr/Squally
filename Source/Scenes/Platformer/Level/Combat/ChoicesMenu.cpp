#include "ChoicesMenu.h"

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
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
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

ChoicesMenu* ChoicesMenu::create(bool noItems, bool noDefend)
{
	ChoicesMenu* instance = new ChoicesMenu(noItems, noDefend);

	instance->autorelease();

	return instance;
}

ChoicesMenu::ChoicesMenu(bool noItems, bool noDefend)
{
	this->noItems = noItems;
	this->noDefend = noDefend;
	this->selectedEntry = nullptr;
	this->currentMenu = CombatEvents::MenuStateArgs::CurrentMenu::Closed;

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

	const float AngleDelta = float(M_PI) / 6.0f;

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
			this->currentMenu = combatArgs->currentMenu;

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

	if (!this->noItems)
	{
		this->itemsNode->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->onItemsClick(); });
	}
	else
	{
		this->itemsNode->disableInteraction();
	}

	this->attackNode->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->onAttackClick(); });

	if (!this->noDefend)
	{
		this->defendNode->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->onDefendClick(); });
	}
	else
	{
		this->defendNode->disableInteraction();
	}
}

void ChoicesMenu::update(float dt)
{
	super::update(dt);
}

void ChoicesMenu::onItemsClick()
{
	switch (this->currentMenu)
	{
		case CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect:
		{
			CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ItemSelect, this->selectedEntry));
			break;
		}
		default:
		{
			CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect, this->selectedEntry));
			break;
		}
	}
}

void ChoicesMenu::onAttackClick()
{
	switch (this->currentMenu)
	{
		case CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect:
		{
			CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::AttackSelect, this->selectedEntry));
			break;
		}
		default:
		{
			CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect, this->selectedEntry));
			break;
		}
	}
}

void ChoicesMenu::onDefendClick()
{
	switch (this->currentMenu)
	{
		case CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect:
		{
			CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::DefendSelect, this->selectedEntry));
			break;
		}
		default:
		{
			CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect, this->selectedEntry));
			break;
		}
	}
}

void ChoicesMenu::toggleInnerText(bool isVisible)
{
	this->itemsNode->setTextVisible(isVisible);
	this->attackNode->setTextVisible(isVisible);
	this->defendNode->setTextVisible(isVisible);

	this->itemsNode->setOpacity((this->noItems || !isVisible) ? 127 : 255);
	this->attackNode->setOpacity(isVisible ? 255 : 127);
	this->defendNode->setOpacity((this->noDefend || !isVisible) ? 127 : 255);
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
	this->attackListNodes.clear();
	this->attackListNode->removeAllChildren();

	if (this->selectedEntry == nullptr)
	{
		return;
	}

	PlatformerEntity* entity = this->selectedEntry->getEntity();

	if (entity == nullptr)
	{
		return;
	}

	EntityAttackBehavior* attackBehavior = entity->getAttachedBehavior<EntityAttackBehavior>();

	if (attackBehavior == nullptr)
	{
		return;
	}

	std::vector<PlatformerAttack*> attacks = attackBehavior->getAttacks();

	this->buildAttackList(this->attackListNode, &this->attackListNodes, attacks, UIResources::Combat_AttackCircle);
}

void ChoicesMenu::buildItemList()
{
	this->itemListNodes.clear();
	this->itemListNode->removeAllChildren();

	if (this->selectedEntry == nullptr)
	{
		return;
	}
	
	PlatformerEntity* entity = this->selectedEntry->getEntity();

	if (entity == nullptr)
	{
		return;
	}

	EntityAttackBehavior* attackBehavior = entity->getAttachedBehavior<EntityAttackBehavior>();

	if (attackBehavior == nullptr)
	{
		return;
	}

	std::vector<PlatformerAttack*> attacks = attackBehavior->getAvailableConsumables();

	this->buildAttackList(this->itemListNode, &this->itemListNodes, attacks, UIResources::Combat_ItemsCircle);
}
	
void ChoicesMenu::buildAttackList(Node* nodeRef, std::vector<ClickableTextNode*>* listRef, std::vector<PlatformerAttack*> attacks, std::string backgroundResource)
{
	const float AngleDelta = float(M_PI) / 6.0f;
	float currentAngle = 0.0f;
	
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

		ClickableTextNode* node = ClickableTextNode::create(attackLabel, attackLabelSelected, backgroundResource, backgroundResource);

		node->setTextOffset(Vec2(48.0f, 0.0f));
		node->setPosition(Vec2(ChoicesMenu::OuterChoicesRadius * std::cos(currentAngle), ChoicesMenu::OuterChoicesRadius * std::sin(currentAngle)));
		node->addChild(Sprite::create(attack->getIconResource()));

		node->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
		{	
			this->selectedEntry->stageCast(attack);

			switch (attack->getAttackType())
			{
				case PlatformerAttack::AttackType::Healing:
				case PlatformerAttack::AttackType::ProjectileHealing:
				case PlatformerAttack::AttackType::ProjectileBuffSpeed:
				{
					CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget, this->selectedEntry));
					break;
				}
				case PlatformerAttack::AttackType::Damage:
				case PlatformerAttack::AttackType::ProjectileDamage:
				{
					CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget, this->selectedEntry));
					break;
				}
				default:
				{
					CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget, this->selectedEntry));
					break;
				}
			}
		});

		currentAngle = (currentAngle <= 0.0f ? 1.0f : -1.0f) * (std::abs(currentAngle) + (currentAngle <= 0.0f ? AngleDelta : 0.0f));

		listRef->push_back(node);
		nodeRef->addChild(node);
	}
}
