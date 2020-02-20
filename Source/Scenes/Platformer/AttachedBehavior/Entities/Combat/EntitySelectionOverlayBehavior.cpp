#include "EntitySelectionOverlayBehavior.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EntitySelectionOverlayBehavior::MapKeyAttachedBehavior = "combat-selection-overlays";

EntitySelectionOverlayBehavior* EntitySelectionOverlayBehavior::create(GameObject* owner)
{
	EntitySelectionOverlayBehavior* instance = new EntitySelectionOverlayBehavior(owner);

	instance->autorelease();

	return instance;
}

EntitySelectionOverlayBehavior::EntitySelectionOverlayBehavior(GameObject* owner) : super(owner)
{
	this->entity = static_cast<PlatformerEntity*>(owner);
	this->lightRay = Sprite::create(UIResources::Combat_SelectionLight);

	this->lightRay->setVisible(false);
	this->lightRay->setAnchorPoint(Vec2(0.5f, 0.0f));

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->lightRay);
}

EntitySelectionOverlayBehavior::~EntitySelectionOverlayBehavior()
{
}

void EntitySelectionOverlayBehavior::onLoad()
{
	const Vec2 LightOffset = Vec2(128.0f, -256.0f);

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeEnable, [=](EventCustom* eventCustom)
	{
		this->setVisible(false);
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeDisable, [=](EventCustom* eventCustom)
	{
		this->setVisible(true);
	}));

	if (dynamic_cast<PlatformerEnemy*>(this->entity) != nullptr)
	{
		this->lightRay->setFlippedX(true);
		this->lightRay->setPosition(this->entity->getEntityCenterPoint() + Vec2(-LightOffset.x, LightOffset.y));
	}
	else
	{
		this->lightRay->setPosition(this->entity->getEntityCenterPoint() + LightOffset);
	}

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventSelectionChanged, [=](EventCustom* eventCustom)
	{
		CombatEvents::SelectionArgs* args = static_cast<CombatEvents::SelectionArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->lightRay->setVisible(args->target == this->entity);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventChangeMenuState, [=](EventCustom* args)
	{
		CombatEvents::MenuStateArgs* combatArgs = static_cast<CombatEvents::MenuStateArgs*>(args->getUserData());

		if (combatArgs != nullptr)
		{
			switch (combatArgs->currentMenu)
			{
				case CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect:
				case CombatEvents::MenuStateArgs::CurrentMenu::AttackSelect:
				case CombatEvents::MenuStateArgs::CurrentMenu::DefendSelect:
				case CombatEvents::MenuStateArgs::CurrentMenu::ItemSelect:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget:
				{
					this->setVisible(true);
					break;
				}
				default:
				{
					this->setVisible(false);
					break;
				}
			}
		}
	}));
}
