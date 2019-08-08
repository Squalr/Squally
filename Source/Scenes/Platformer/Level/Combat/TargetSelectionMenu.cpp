#include "TargetSelectionMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/AttachedBehaviors/Combat/Entities/EntitySelectionBehavior.h"

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
					this->selectEntity(nullptr);

					ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEnemy>([=](PlatformerEnemy* entity, bool* isHandled)
					{
						if (!entity->isDead())
						{
							this->selectEntity(entity);

							*isHandled = true;
						}
					}));

					this->allowedSelection = AllowedSelection::Enemy;
					this->setEntityClickCallbacks();
					this->isActive = true;
					this->setVisible(true);
					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget:
				{
					this->selectEntity(nullptr);

					ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerFriendly>([=](PlatformerFriendly* entity, bool* isHandled)
					{
						if (!entity->isDead())
						{
							this->selectEntity(entity);

							*isHandled = true;
						}
					}));

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

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_A, EventKeyboard::KeyCode::KEY_LEFT_ARROW}, [=](InputEvents::InputArgs* args)
	{
		if (this->isActive)
		{
			this->selectNext(true);
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_D, EventKeyboard::KeyCode::KEY_RIGHT_ARROW}, [=](InputEvents::InputArgs* args)
	{
		if (this->isActive)
		{
			this->selectNext(false);
		}
	});
}

void TargetSelectionMenu::update(float dt)
{
	super::update(dt);
}

void TargetSelectionMenu::selectEntity(PlatformerEntity* entity)
{
	const Vec2 LightOffset = Vec2(128.0f, -128.0f);

	if (entity != nullptr)
	{
		this->lightRay->setPosition(GameUtils::getScreenBounds(entity).origin + LightOffset);
		this->lightRay->setVisible(true);
	}
	else
	{
		this->lightRay->setVisible(false);
	}

	this->selectedEntity = entity;
}

void TargetSelectionMenu::selectNext(bool directionIsLeft)
{
	std::vector<PlatformerEntity*> targetEntityGroup = std::vector<PlatformerEntity*>();

	switch (this->allowedSelection)
	{
		case AllowedSelection::Player:
		{
			ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerFriendly>([&](PlatformerFriendly* entity)
			{
				if (!entity->isDead())
				{
					targetEntityGroup.push_back(entity);
				}
			}));

			break;
		}
		case AllowedSelection::Either:
		{
			ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEntity* entity)
			{
				if (!entity->isDead())
				{
					targetEntityGroup.push_back(entity);
				}
			}));

			break;
		}
		case AllowedSelection::Enemy:
		{
			ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEnemy* entity)
			{
				if (!entity->isDead())
				{
					targetEntityGroup.push_back(entity);
				}
			}));

			break;
		}
		default:
		{
			break;
		}
	}

	auto entityPosition = std::find(targetEntityGroup.begin(), targetEntityGroup.end(), this->selectedEntity);

	if (entityPosition != std::end(targetEntityGroup))
	{
		if (directionIsLeft)
		{
			PlatformerEntity* nextEntity = (*entityPosition == targetEntityGroup.front()) ? targetEntityGroup.back() : *std::prev(entityPosition);

			this->selectEntity(nextEntity);
		}
		else
		{
			auto next = std::next(entityPosition);

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
	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEntity>([=](PlatformerEntity* entity)
	{
		EntitySelectionBehavior* selection = entity->getAttachedBehavior<EntitySelectionBehavior>();
		
		if (selection != nullptr)
		{
			if (entity->isDead() 
				|| (this->allowedSelection == AllowedSelection::Player && dynamic_cast<PlatformerFriendly*>(entity) == nullptr)
				|| (this->allowedSelection == AllowedSelection::Enemy && dynamic_cast<PlatformerEnemy*>(entity) == nullptr))
			{
				return;
			}

			selection->setEntityClickCallbacks([=]()
			{
				CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::Closed, nullptr));
				CombatEvents::TriggerSelectCastTarget(CombatEvents::CastTargetArgs(entity));
			},
			[=]()
			{
				this->selectEntity(entity);
			});
		}
	}));
}

void TargetSelectionMenu::clearEntityClickCallbacks()
{
	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEntity>([=](PlatformerEntity* entity)
	{
		EntitySelectionBehavior* selection = entity->getAttachedBehavior<EntitySelectionBehavior>();
		
		if (selection != nullptr)
		{
			selection->clearEntityClickCallbacks();
		}
	}));
}
