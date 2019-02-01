#include "TargetSelectionMenu.h"

#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/CProgressBar.h"
#include "Engine/Utils/GameUtils.h"
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

TargetSelectionMenu* TargetSelectionMenu::create()
{
	TargetSelectionMenu* instance = new TargetSelectionMenu();

	instance->autorelease();

	return instance;
}

TargetSelectionMenu::TargetSelectionMenu()
{
	this->lightRay = Sprite::create(UIResources::Combat_SelectionLight);

	this->lightRay->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->addChild(this->lightRay);
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
		CombatEvents::MenuStateArgs* combatArgs = static_cast<CombatEvents::MenuStateArgs*>(args->getUserData());

		if (combatArgs != nullptr && combatArgs->entry != nullptr)
		{
			switch (combatArgs->currentMenu)
			{
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget:
				{
					if (!this->enemyEntities.empty())
					{
						this->selectEntity(this->enemyEntities.front());
					}

					this->allowedSelection = AllowedSelection::Enemy;
					this->setEntityClickCallbacks();
					this->isActive = true;
					this->setVisible(true);
					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget:
				{
					if (!this->playerEntities.empty())
					{
						this->selectEntity(this->playerEntities.front());
					}

					this->allowedSelection = AllowedSelection::Player;
					this->setEntityClickCallbacks();
					this->isActive = true;
					this->setVisible(true);
					break;
				}
				default:
				{
					this->clearEntityClickCallbacks();
					this->setVisible(false);
					break;
				}
			}
		}
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(TargetSelectionMenu::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

void TargetSelectionMenu::update(float dt)
{
	super::update(dt);
}

void TargetSelectionMenu::initializeEntities(std::vector<PlatformerEntity*> playerEntities, std::vector<PlatformerEntity*> enemyEntities)
{
	this->playerEntities = playerEntities;
	this->enemyEntities = enemyEntities;
}

void TargetSelectionMenu::selectEntity(PlatformerEntity* entity)
{
	const Vec2 LightOffset = Vec2(128.0f, -128.0f);

	this->lightRay->setPosition(entity->getPosition() + LightOffset);
	this->lightRay->setPositionZ(GameUtils::getDepth(entity));

	this->selectedEntity = entity;
}

void TargetSelectionMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!this->isActive)
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_A:
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		{
			if (this->allowedSelection == AllowedSelection::Player || this->allowedSelection == AllowedSelection::Either)
			{
				auto playerEntitiesPos = std::find(this->playerEntities.begin(), this->playerEntities.end(), this->selectedEntity);

				if (playerEntitiesPos != std::end(this->playerEntities))
				{
					if (*playerEntitiesPos == this->playerEntities.front())
					{
						this->selectEntity(this->playerEntities.back());
					}
					else
					{
						this->selectEntity(*std::prev(playerEntitiesPos));
					}
				}
			}

			if (this->allowedSelection == AllowedSelection::Enemy || this->allowedSelection == AllowedSelection::Either)
			{
				auto enemyEntitiesPos = std::find(this->enemyEntities.begin(), this->enemyEntities.end(), this->selectedEntity);

				if (enemyEntitiesPos != std::end(this->enemyEntities))
				{
					if (*enemyEntitiesPos == this->enemyEntities.front())
					{
						this->selectEntity(this->enemyEntities.back());
					}
					else
					{
						this->selectEntity(*std::prev(enemyEntitiesPos));
					}
				}
			}

			break;
		}
		case EventKeyboard::KeyCode::KEY_D:
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			if (this->allowedSelection == AllowedSelection::Player || this->allowedSelection == AllowedSelection::Either)
			{
				auto playerEntitiesPos = std::find(this->playerEntities.begin(), this->playerEntities.end(), this->selectedEntity);

				if (playerEntitiesPos != std::end(this->playerEntities))
				{
					auto next = std::next(playerEntitiesPos);

					if (next != std::end(this->playerEntities))
					{
						this->selectEntity(*next);
					}
					else
					{
						this->selectEntity(this->playerEntities.front());
					}
				}
			}

			if (this->allowedSelection == AllowedSelection::Enemy || this->allowedSelection == AllowedSelection::Either)
			{
				auto enemyEntitiesPos = std::find(this->enemyEntities.begin(), this->enemyEntities.end(), this->selectedEntity);

				if (enemyEntitiesPos != std::end(this->enemyEntities))
				{
					auto next = std::next(enemyEntitiesPos);

					if (next != std::end(this->enemyEntities))
					{
						this->selectEntity(*next);
					}
					else
					{
						this->selectEntity(this->enemyEntities.front());
					}
				}
			}

			break;
		}
		default:
		{
			break;
		}
	}
}

void TargetSelectionMenu::setEntityClickCallbacks()
{
	if (this->allowedSelection == AllowedSelection::Player || this->allowedSelection == AllowedSelection::Either)
	{
		for (auto it = this->playerEntities.begin(); it != this->playerEntities.end(); it++)
		{
			PlatformerEntity* entity = *it;

			entity->clickHitbox->enableInteraction();
			entity->clickHitbox->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*)
			{
				CombatEvents::TriggerSelectCastTarget(CombatEvents::CastTargetArgs(entity));
			});
			entity->clickHitbox->setMouseOverCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*)
			{
				this->selectEntity(entity);
			});
		}
	}

	if (this->allowedSelection == AllowedSelection::Enemy || this->allowedSelection == AllowedSelection::Either)
	{
		for (auto it = this->enemyEntities.begin(); it != this->enemyEntities.end(); it++)
		{
			PlatformerEntity* entity = *it;

			entity->clickHitbox->enableInteraction();
			entity->clickHitbox->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*)
			{
				CombatEvents::TriggerSelectCastTarget(CombatEvents::CastTargetArgs(entity));
			});
			entity->clickHitbox->setMouseOverCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*)
			{
				this->selectEntity(entity);
			});
		}
	}
}

void TargetSelectionMenu::clearEntityClickCallbacks()
{
	for (auto it = this->playerEntities.begin(); it != this->playerEntities.end(); it++)
	{
		PlatformerEntity* entity = *it;

		entity->clickHitbox->disableInteraction();
		entity->clickHitbox->setClickCallback(nullptr);
		entity->clickHitbox->setMouseOverCallback(nullptr);
	}

	for (auto it = this->enemyEntities.begin(); it != this->enemyEntities.end(); it++)
	{
		PlatformerEntity* entity = *it;

		entity->clickHitbox->disableInteraction();
		entity->clickHitbox->setClickCallback(nullptr);
		entity->clickHitbox->setMouseOverCallback(nullptr);
	}
}
