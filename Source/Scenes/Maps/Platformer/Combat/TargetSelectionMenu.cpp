#include "TargetSelectionMenu.h"

#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"

#include "Resources/UIResources.h"

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
	this->completeEntityList = std::vector<PlatformerEntity*>();

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

		if (combatArgs != nullptr)
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

	this->completeEntityList.clear();
}

void TargetSelectionMenu::selectEntity(PlatformerEntity* entity)
{
	const Vec2 LightOffset = Vec2(128.0f, -128.0f);

	if (entity != nullptr)
	{
		this->lightRay->setPosition(entity->getPosition() + LightOffset);
		this->lightRay->setPositionZ(GameUtils::getDepth(entity));
		this->lightRay->setVisible(true);
	}
	else
	{
		this->lightRay->setVisible(false);
	}

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
			this->selectNextLeft();

			break;
		}
		case EventKeyboard::KeyCode::KEY_D:
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			this->selectNextRight();

			break;
		}
		default:
		{
			break;
		}
	}
}

void TargetSelectionMenu::selectNextLeft(int callCount)
{
	std::vector<PlatformerEntity*>* targetEntityGroup = nullptr;

	switch (this->allowedSelection)
	{
		case AllowedSelection::Player:
		{
			targetEntityGroup = &this->playerEntities;
			break;
		}
		case AllowedSelection::Either:
		{
			targetEntityGroup = &this->completeEntityList;
			break;
		}
		case AllowedSelection::Enemy:
		{
			targetEntityGroup = &this->enemyEntities;
			break;
		}
		default:
		{
			break;
		}
	}

	if (targetEntityGroup == nullptr)
	{
		return;
	}

	// Infinite loop breaker
	if (callCount > targetEntityGroup->size())
	{
		this->selectEntity(nullptr);

		return;
	}

	auto entityPosition = std::find(targetEntityGroup->begin(), targetEntityGroup->end(), this->selectedEntity);

	if (entityPosition != std::end(*targetEntityGroup))
	{
		PlatformerEntity* nextEntity = (*entityPosition == targetEntityGroup->front()) ? this->playerEntities.back() : *std::prev(entityPosition);

		this->selectEntity(nextEntity);

		// Next entity is dead! Try the next left target
		if (nextEntity->isDead())
		{
			this->selectNextLeft(++callCount);
			return;
		}
	}
}

void TargetSelectionMenu::selectNextRight(int callCount)
{
	std::vector<PlatformerEntity*>* targetEntityGroup = nullptr;

	switch (this->allowedSelection)
	{
		case AllowedSelection::Player:
		{
			targetEntityGroup = &this->playerEntities;
			break;
		}
		case AllowedSelection::Either:
		{
			targetEntityGroup = &this->completeEntityList;
			break;
		}
		case AllowedSelection::Enemy:
		{
			targetEntityGroup = &this->enemyEntities;
			break;
		}
		default:
		{
			break;
		}
	}

	if (targetEntityGroup == nullptr)
	{
		return;
	}

	// Infinite loop breaker
	if (callCount > targetEntityGroup->size())
	{
		this->selectEntity(nullptr);

		return;
	}
	
	auto entityPosition = std::find(targetEntityGroup->begin(), targetEntityGroup->end(), this->selectedEntity);

	if (entityPosition != std::end(*targetEntityGroup))
	{
		auto next = std::next(entityPosition);

		PlatformerEntity* nextEntity = (next != std::end(*targetEntityGroup)) ? *next : targetEntityGroup->front();

		this->selectEntity(nextEntity);

		// Next entity is dead! Try the next right target
		if (nextEntity->isDead())
		{
			this->selectNextRight(++callCount);
			return;
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

			if (entity->isDead())
			{
				continue;
			}

			entity->clickHitbox->enableInteraction();
			entity->clickHitbox->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*)
			{
				CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::Closed, nullptr));
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

			if (entity->isDead())
			{
				continue;
			}

			entity->clickHitbox->enableInteraction();
			entity->clickHitbox->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*)
			{
				CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::Closed, nullptr));
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
