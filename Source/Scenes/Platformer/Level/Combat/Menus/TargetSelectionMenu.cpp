#include "TargetSelectionMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCInputEvents.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntitySelectionBehavior.h"
#include "Scenes/Platformer/Level/Combat/Menus/ChooseTargetMenu.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

TargetSelectionMenu* TargetSelectionMenu::create(Timeline* timelineRef)
{
	TargetSelectionMenu* instance = new TargetSelectionMenu(timelineRef);

	instance->autorelease();

	return instance;
}

TargetSelectionMenu::TargetSelectionMenu(Timeline* timelineRef)
{
	this->timelineRef = timelineRef;
	this->selectedEntity = nullptr;
	this->allowedSelection = AllowedSelection::None;
	this->chooseTargetMenu = ChooseTargetMenu::create();

	this->addChild(this->chooseTargetMenu);
}

void TargetSelectionMenu::onEnter()
{
	super::onEnter();

	this->setVisible(false);

	this->scheduleUpdate();
}

void TargetSelectionMenu::initializePositions()
{
	super::initializePositions();
}

void TargetSelectionMenu::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventChangeMenuState, [=](EventCustom* args)
	{
		CombatEvents::MenuStateArgs* combatArgs = static_cast<CombatEvents::MenuStateArgs*>(args->getData());

		if (combatArgs != nullptr)
		{
			switch (combatArgs->currentMenu)
			{
				case CombatEvents::MenuStateArgs::CurrentMenu::DefendSelect:
				{
					// For now, there is no defend select menu. Just wait for this state to pass.
					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect:
				case CombatEvents::MenuStateArgs::CurrentMenu::ItemSelect:
				case CombatEvents::MenuStateArgs::CurrentMenu::AttackSelect:
				{
					this->allowedSelection = AllowedSelection::None;
					this->clearEntityClickCallbacks();
					this->selectEntity(combatArgs->entry == nullptr ? nullptr : combatArgs->entry->getEntity());

					this->setVisible(true);

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget:
				{
					this->allowedSelection = AllowedSelection::Enemy;
					this->isActive = true;

					this->setEntityClickCallbacks();
					this->selectEntity(nullptr);
					this->selectNext(false);

					this->setVisible(true);
					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseResurrectionTarget:
				{
					this->allowedSelection = AllowedSelection::PlayerResurrection;
					this->isActive = true;

					this->setEntityClickCallbacks();
					this->selectEntity(nullptr);
					this->selectNext(false);
					
					this->setVisible(true);
					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget:
				{
					this->allowedSelection = AllowedSelection::Player;
					this->isActive = true;

					this->setEntityClickCallbacks();
					this->selectEntity(nullptr);
					this->selectNext(false);
					
					this->setVisible(true);
					break;
				}
				default:
				{
					this->selectEntity(nullptr);
					this->allowedSelection = AllowedSelection::None;
					this->clearEntityClickCallbacks();
					break;
				}
			}
		}
	}));

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_A, InputEvents::KeyCode::KEY_LEFT_ARROW }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->selectNext(true);
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_D, InputEvents::KeyCode::KEY_RIGHT_ARROW }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->selectNext(false);
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_ENTER, InputEvents::KeyCode::KEY_SPACE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->chooseCurrentTarget();
	});
}

void TargetSelectionMenu::update(float dt)
{
	super::update(dt);
}

void TargetSelectionMenu::chooseCurrentTarget()
{
	if (!this->isActive || this->selectedEntity == nullptr)
	{
		return;
	}

	CombatEvents::TriggerSelectCastTarget(CombatEvents::CastTargetsArgs({ this->selectedEntity }));
}

void TargetSelectionMenu::selectEntity(PlatformerEntity* entity)
{
	this->selectedEntity = entity;
	
	CombatEvents::TriggerSelectionChanged(CombatEvents::SelectionArgs(this->selectedEntity));
}

void TargetSelectionMenu::selectNext(bool directionIsLeft)
{
	if (!this->isActive || this->allowedSelection == AllowedSelection::None)
	{
		return;
	}

	std::vector<PlatformerEntity*> targetEntityGroup = std::vector<PlatformerEntity*>();

	for (auto next : timelineRef->getEntries())
	{
		PlatformerEntity* entity = next->getEntity();

		if (entity->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			if (this->allowedSelection == AllowedSelection::Either
				|| (next->isPlayerEntry() && this->allowedSelection == AllowedSelection::Player)
				|| (!next->isPlayerEntry() && this->allowedSelection == AllowedSelection::Enemy))
			{
				targetEntityGroup.push_back(entity);
			}
		}
		else if (next->isPlayerEntry() && this->allowedSelection == AllowedSelection::PlayerResurrection)
		{
			targetEntityGroup.push_back(entity);
		}
	}

	if (targetEntityGroup.empty())
	{
		if (directionIsLeft)
		{
			CombatEvents::TriggerMenuGoBack();
		}

		return;
	}

	auto entityPosition = std::find(targetEntityGroup.begin(), targetEntityGroup.end(), this->selectedEntity);

	if (this->selectedEntity == nullptr)
	{
		this->selectEntity(targetEntityGroup.front());
	}
	else if (entityPosition != std::end(targetEntityGroup))
	{
		if (directionIsLeft)
		{
			// Looping feels more natural when scrolling right, whereas going back is more natural when scrolling left
			if (*entityPosition == targetEntityGroup.front())
			{
				CombatEvents::TriggerMenuGoBack();
				return;
			}

			PlatformerEntity* nextEntity = (*entityPosition == targetEntityGroup.front()) ? targetEntityGroup.back() : *std::prev(entityPosition);

			this->selectEntity(nextEntity);
		}
		else
		{
			auto next = std::next(entityPosition);

			// Cycle next entity
			PlatformerEntity* nextEntity = (next != std::end(targetEntityGroup)) ? *next : targetEntityGroup.front();

			this->selectEntity(nextEntity);
		}
	}
	else
	{
		this->selectEntity(nullptr);
	}
}

void TargetSelectionMenu::setEntityClickCallbacks()
{
	for (auto next : timelineRef->getEntries())
	{
		this->setEntityClickCallbacks(next->getEntity());
	}
}

void TargetSelectionMenu::setEntityClickCallbacks(PlatformerEntity* entity)
{
	entity->getAttachedBehavior<EntitySelectionBehavior>([=](EntitySelectionBehavior* selection)
	{
		TimelineEntry* entry = this->timelineRef->getAssociatedEntry(entity);
		bool isAlive = entity->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true);

		switch(this->allowedSelection)
		{
			case AllowedSelection::PlayerResurrection:
			{
				if (!entry->isPlayerEntry() || isAlive)
				{
					return;
				}

				break;
			}
			case AllowedSelection::Player:
			{
				if (!entry->isPlayerEntry() || !isAlive)
				{
					return;
				}
			}
			case AllowedSelection::Enemy:
			{
				if (entry->isPlayerEntry() || !isAlive)
				{
					return;
				}
			}
			default:
			{
				break;
			}
		}

		PlatformerEntity* entityRef = entity;

		selection->setEntityClickCallbacks([=]()
		{
			CombatEvents::TriggerSelectCastTarget(CombatEvents::CastTargetsArgs({ entityRef }));
		},
		[=]()
		{
			this->selectEntity(entityRef);
		});
	});
}

void TargetSelectionMenu::clearEntityClickCallbacks()
{
	for (auto next : timelineRef->getEntries())
	{
		EntitySelectionBehavior* selection = next->getEntity()->getAttachedBehavior<EntitySelectionBehavior>();
		
		if (selection != nullptr)
		{
			selection->clearEntityClickCallbacks();
		}
	}
}
