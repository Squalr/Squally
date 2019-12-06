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
#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/AttackMenu.h"
#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/ItemsMenu.h"
#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/RadialScrollMenu.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float ChoicesMenu::Radius = 240.0f;

ChoicesMenu* ChoicesMenu::create()
{
	ChoicesMenu* instance = new ChoicesMenu();

	instance->autorelease();

	return instance;
}

ChoicesMenu::ChoicesMenu()
{
	this->noItems = false;
	this->noDefend = false;
	this->selectedEntry = nullptr;
	this->currentMenu = CombatEvents::MenuStateArgs::CurrentMenu::Closed;
	this->choicesMenu = RadialScrollMenu::create(ChoicesMenu::Radius);
	this->attackMenu = AttackMenu::create();
	this->itemsMenu = ItemsMenu::create();

	this->itemsButton = this->choicesMenu->addEntry(Strings::Platformer_Combat_Items::create(), Sprite::create(UIResources::Menus_Icons_Dice), UIResources::Combat_ItemsCircle, [=]()
	{
		this->onItemsClick();
	});

	this->attackButton = this->choicesMenu->addEntry(Strings::Platformer_Combat_Attack::create(), Sprite::create(UIResources::Menus_Icons_Spear), UIResources::Combat_AttackCircle, [=]()
	{
		this->onAttackClick();
	});

	this->defendButton = this->choicesMenu->addEntry(Strings::Platformer_Combat_Defend::create(), Sprite::create(UIResources::Menus_Icons_ShieldBroken), UIResources::Combat_DefendCircle, [=]()
	{
		this->onDefendClick();
	});

	this->addChild(this->choicesMenu);
	this->addChild(this->attackMenu);
	this->addChild(this->itemsMenu);
}

ChoicesMenu::~ChoicesMenu()
{
}

void ChoicesMenu::onEnter()
{
	super::onEnter();

	this->setVisible(false);
}

void ChoicesMenu::initializePositions()
{
	super::initializePositions();
}

void ChoicesMenu::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventDisableDefend, [=](EventCustom* eventCustom)
	{
		this->noDefend = true;
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventDisableDefend, [=](EventCustom* eventCustom)
	{
		this->noItems = true;
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventChangeMenuState, [=](EventCustom* eventCustom)
	{
		CombatEvents::MenuStateArgs* combatArgs = static_cast<CombatEvents::MenuStateArgs*>(eventCustom->getUserData());

		if (combatArgs != nullptr)
		{
			this->currentMenu = combatArgs->currentMenu;

			switch (combatArgs->currentMenu)
			{
				case CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect:
				{
					this->attackMenu->setVisible(false);
					// this->defendMenu->setVisible(false);
					this->itemsMenu->setVisible(false);

					this->setSelectedEntry(combatArgs->entry);

					this->setVisible(true);
					this->choicesMenu->enableAll();

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::AttackSelect:
				{
					this->attackMenu->setVisible(true);
					// this->defendMenu->setVisible(false);
					this->itemsMenu->setVisible(false);

					this->attackMenu->enableAll();
					this->choicesMenu->disableAll();

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ItemSelect:
				{
					this->attackMenu->setVisible(false);
					// this->defendMenu->setVisible(false);
					this->itemsMenu->setVisible(true);

					this->itemsMenu->enableAll();
					this->choicesMenu->disableAll();

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::DefendSelect:
				{
					this->attackMenu->setVisible(false);
					// this->defendMenu->setVisible(true);
					this->itemsMenu->setVisible(false);

					// this->defendMenu->enableAll();
					this->choicesMenu->disableAll();

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget:
				{
					this->attackMenu->disableAll();
					this->itemsMenu->disableAll();
					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::Closed:
				{
					this->attackMenu->setVisible(false);
					// this->defendMenu->setVisible(false);
					this->itemsMenu->setVisible(false);
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

	if (this->noItems)
	{
		this->itemsButton->disableInteraction();
	}

	if (this->noDefend)
	{
		this->defendButton->disableInteraction();
	}
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

void ChoicesMenu::setSelectedEntry(TimelineEntry* selectedEntry)
{
	this->selectedEntry = selectedEntry;

	this->attackMenu->buildAttackList(selectedEntry);
	this->itemsMenu->buildAttackList(selectedEntry);
}
