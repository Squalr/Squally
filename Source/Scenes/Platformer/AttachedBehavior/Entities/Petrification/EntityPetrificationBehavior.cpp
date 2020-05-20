#include "EntityPetrificationBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string EntityPetrificationBehavior::MapKey = "petrified";

EntityPetrificationBehavior* EntityPetrificationBehavior::create(GameObject* owner)
{
	EntityPetrificationBehavior* instance = new EntityPetrificationBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityPetrificationBehavior::EntityPetrificationBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->petrifiedSprite = nullptr;
	this->displayOffset = Vec2::ZERO;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		if (this->entity->getEntityKey() == "ajax")
		{
			this->petrifiedSprite = Sprite::create(EntityResources::Npcs_UnderflowRuins_Ajax_Petrified);
			this->displayOffset = Vec2(58.0f, 0.0f);
		}
		else if (this->entity->getEntityKey() == "aphrodite")
		{
			this->petrifiedSprite = Sprite::create(EntityResources::Npcs_UnderflowRuins_Aphrodite_Petrified);
			this->displayOffset = Vec2(2.0f, 0.0f);
		}
		else if (this->entity->getEntityKey() == "griffin")
		{
			this->petrifiedSprite = Sprite::create(EntityResources::Npcs_UnderflowRuins_Griffin_Petrified);
			this->displayOffset = Vec2(40.0f, -2.0f);
		}
		else if (this->entity->getEntityKey() == "geryon")
		{
			this->petrifiedSprite = Sprite::create(EntityResources::Npcs_UnderflowRuins_Geryon_Petrified);
			this->displayOffset = Vec2(28.0f, -4.0f);
		}
		else if (this->entity->getEntityKey() == "athena")
		{
			this->petrifiedSprite = Sprite::create(EntityResources::Npcs_UnderflowRuins_Athena_Petrified);
			this->displayOffset = Vec2(30.0f, -6.0f);
		}
		else
		{
			this->petrifiedSprite = Sprite::create();
		}

		this->petrifiedSprite->setAnchorPoint(Vec2(0.5f, 0.0f));

		this->addChild(this->petrifiedSprite);
	}
}

EntityPetrificationBehavior::~EntityPetrificationBehavior()
{
}

void EntityPetrificationBehavior::onLoad()
{
	this->petrifiedSprite->setFlippedX(this->entity->isFlippedX());
	this->petrifiedSprite->setPosition(this->petrifiedSprite->isFlippedX() ? Vec2(-this->displayOffset.x, this->displayOffset.y) : this->displayOffset);
	
	// How we achieve the magic of petrification -- mark the entity as dead. All other loaded behaviors should respect this.
	this->entity->watchForAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		healthBehavior->kill();
	});
	
	this->entity->getAnimations()->setVisible(false);
}

void EntityPetrificationBehavior::onDisable()
{
	super::onDisable();

	this->unpetrify();
}

void EntityPetrificationBehavior::unpetrify()
{
	if (this->petrifiedSprite != nullptr)
	{
		this->petrifiedSprite->setVisible(false);
	}

	if (this->entity != nullptr)
	{
		this->entity->setVisible(true);

		this->entity->watchForAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
		{
			healthBehavior->revive();
		});
	}
}
