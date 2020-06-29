#include "ChoicesMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/AttackMenu.h"
#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/ItemsMenu.h"
#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/RadialEntry.h"
#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/RadialScrollMenu.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float ChoicesMenu::Radius = 240.0f;

ChoicesMenu* ChoicesMenu::create(Timeline* timelineRef)
{
	ChoicesMenu* instance = new ChoicesMenu(timelineRef);

	instance->autorelease();

	return instance;
}

ChoicesMenu::ChoicesMenu(Timeline* timelineRef)
{
	this->noItems = false;
	this->noDefend = false;
	this->selectedEntry = nullptr;
	this->currentMenu = CombatEvents::MenuStateArgs::CurrentMenu::Closed;
	this->previousMenu = CombatEvents::MenuStateArgs::CurrentMenu::Closed;
	this->choicesMenu = RadialScrollMenu::create(ChoicesMenu::Radius);
	this->attackMenu = AttackMenu::create(timelineRef);
	this->itemsMenu = ItemsMenu::create();
	this->trackTarget = nullptr;

	this->itemsButton = this->choicesMenu->addEntry(Strings::Platformer_Combat_Items::create(), nullptr, UIResources::Menus_Icons_Dice, UIResources::Combat_ItemsCircle, [=]()
	{
		this->onItemsClick();
	});

	this->attackButton = this->choicesMenu->addEntry(Strings::Platformer_Combat_Attack::create(), nullptr, UIResources::Menus_Icons_SpearTip, UIResources::Combat_AttackCircle, [=]()
	{
		this->onAttackClick();
	});

	this->defendButton = this->choicesMenu->addEntry(Strings::Platformer_Combat_Defend::create(), nullptr, UIResources::Menus_Icons_ShieldBroken, UIResources::Combat_DefendCircle, [=]()
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

	this->scheduleUpdate();
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

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventDisableItems, [=](EventCustom* eventCustom)
	{
		this->noItems = true;
	}));

	// Handle the (very rare) case of getting interrupted while menuing -- can happen if a projectile hits the user after the timeline resumes.
	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventCastInterrupt, [=](EventCustom* eventCustom)
	{
		CombatEvents::CastInterruptArgs* args = static_cast<CombatEvents::CastInterruptArgs*>(eventCustom->getUserData());

		PlatformerEntity* entity = this->selectedEntry == nullptr ? nullptr : this->selectedEntry->getEntity();

		if (args != nullptr && args->target == entity)
		{
			if (this->currentMenu != CombatEvents::MenuStateArgs::CurrentMenu::Closed)
			{
				CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::Closed, this->selectedEntry));
				CombatEvents::TriggerResumeTimeline();
			}
		}
	}));

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE, EventKeyboard::KeyCode::KEY_BACKSPACE }, [=](InputEvents::InputArgs* args)
	{
		switch (this->currentMenu)
		{
			case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget:
			case CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget:
			case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget:
			case CombatEvents::MenuStateArgs::CurrentMenu::ChooseResurrectionTarget:
			{
				args->handle();
				CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(this->previousMenu, this->selectedEntry));	
				break;
			}
			default:
			{
				break;
			}
		}
	});

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventMenuBack, [=](EventCustom* eventCustom)
	{
		CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(this->previousMenu, this->selectedEntry));	
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventChangeMenuState, [=](EventCustom* eventCustom)
	{
		CombatEvents::MenuStateArgs* combatArgs = static_cast<CombatEvents::MenuStateArgs*>(eventCustom->getUserData());

		if (combatArgs != nullptr)
		{
			this->previousMenu = this->currentMenu;
			this->currentMenu = combatArgs->currentMenu;

			this->track(combatArgs->entry == nullptr ? nullptr : combatArgs->entry->getEntity());

			switch (this->currentMenu)
			{
				case CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect:
				{
					PlatformerEvents::TriggerAllowPause();

					this->attackMenu->setVisible(false);
					this->itemsMenu->setVisible(false);
					this->choicesMenu->setVisible(true);
					this->setVisible(true);

					this->setSelectedEntry(combatArgs->entry);
					this->choicesMenu->enableAll();

					if (this->noItems || !this->itemsMenu->hasItems())
					{
						this->itemsButton->disableInteraction(127);
					}
					else
					{
						this->itemsButton->enableInteraction();
					}

					if (this->noDefend)
					{
						this->defendButton->disableInteraction(127);
					}

					if (this->previousMenu == CombatEvents::MenuStateArgs::CurrentMenu::Closed)
					{
						this->choicesMenu->scrollTo(1);
					}

					this->choicesMenu->focus();
					this->itemsMenu->unfocus();
					this->attackMenu->unfocus();

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::AttackSelect:
				{
					PlatformerEvents::TriggerDisallowPause();

					this->attackMenu->setVisible(true);
					this->itemsMenu->setVisible(false);
					this->choicesMenu->setVisible(true);

					this->choicesMenu->toggleAll(false, true);
					this->attackMenu->enableAll();

					this->choicesMenu->unfocus();
					this->itemsMenu->unfocus();
					this->attackMenu->focus();

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ItemSelect:
				{
					PlatformerEvents::TriggerDisallowPause();

					this->attackMenu->setVisible(false);
					this->itemsMenu->setVisible(true);
					this->choicesMenu->setVisible(true);

					this->choicesMenu->toggleAll(false, true);
					this->itemsMenu->enableAll();

					this->choicesMenu->unfocus();
					this->itemsMenu->focus();
					this->attackMenu->unfocus();

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::DefendSelect:
				{
					// For now, there is no defend select menu. Just wait for this state to pass.
					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseResurrectionTarget:
				{
					PlatformerEvents::TriggerDisallowPause();

					this->attackMenu->setVisible(false);
					this->itemsMenu->setVisible(false);
					this->choicesMenu->setVisible(false);

					this->choicesMenu->unfocus();
					this->itemsMenu->unfocus();
					this->attackMenu->unfocus();
					break;
				}
				default:
				case CombatEvents::MenuStateArgs::CurrentMenu::Closed:
				{
					PlatformerEvents::TriggerAllowPause();

					this->attackMenu->setVisible(false);
					this->itemsMenu->setVisible(false);
					this->choicesMenu->setVisible(false);
					this->setVisible(false);

					this->choicesMenu->unfocus();
					this->itemsMenu->unfocus();
					this->attackMenu->unfocus();

					break;
				}
			}
		}
	}));

	this->itemsMenu->setBackCallback([=]()
	{
		CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect, this->selectedEntry));	
	});

	this->attackMenu->setBackCallback([=]()
	{
		CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect, this->selectedEntry));	
	});
}

void ChoicesMenu::update(float dt)
{
	super::update(dt);

	static const Vec2 Offset = Vec2(-64.0f, 0.0f);

	if (this->trackTarget != nullptr)
	{
		this->setPosition(GameUtils::getScreenBounds(this->trackTarget).origin + this->trackTarget->getEntityCenterPoint() + Offset);
	}
}

void ChoicesMenu::onItemsClick()
{
	this->itemsMenu->scrollTo(1);

	if (this->currentMenu == CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect && this->choicesMenu->getIndex() == 0)
	{
		CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ItemSelect, this->selectedEntry));
	}
	else
	{
		CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect, this->selectedEntry));
	}

	this->choicesMenu->scrollTo(0);
}

void ChoicesMenu::onAttackClick()
{
	this->attackMenu->scrollTo(1);

	if (this->currentMenu == CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect && this->choicesMenu->getIndex() == 1)
	{
		CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::AttackSelect, this->selectedEntry));
	}
	else
	{
		CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect, this->selectedEntry));
	}

	this->choicesMenu->scrollTo(1);
}

void ChoicesMenu::onDefendClick()
{
	/*
	if (this->currentMenu == CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect && this->choicesMenu->getIndex() == 2)
	{
		CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::DefendSelect, this->selectedEntry));
	}
	else
	{
		CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect, this->selectedEntry));
	}*/
	
	CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::DefendSelect, this->selectedEntry));
	
	this->choicesMenu->scrollTo(2);
}

void ChoicesMenu::setSelectedEntry(TimelineEntry* selectedEntry)
{
	this->selectedEntry = selectedEntry;

	this->attackMenu->buildAttackList(selectedEntry);
	this->itemsMenu->buildItemList(selectedEntry);
}

void ChoicesMenu::track(PlatformerEntity* trackTarget)
{
	this->trackTarget = trackTarget;
}
