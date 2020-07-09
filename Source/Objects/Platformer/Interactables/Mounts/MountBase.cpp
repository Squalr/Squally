#include "MountBase.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/ItemPools/RecipePools/RecipePoolDeserializer.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Movement/EntityMountBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

MountBase::MountBase(ValueMap& properties, Size size) : super(properties, InteractObject::InteractType::Input, size)
{
	this->backNode = Node::create();
	this->reparentNode = Node::create();
	this->frontNode = Node::create();
	this->mountedEntity = nullptr;

	this->addChild(this->backNode);
	this->addChild(this->reparentNode);
	this->addChild(this->frontNode);
}

MountBase::~MountBase()
{
}

Node* MountBase::getReparentNode()
{
	return this->reparentNode;
}

Vec2 MountBase::getReparentPosition()
{
	return Vec2::ZERO;
}

void MountBase::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void MountBase::update(float dt)
{
	super::update(dt);

	this->setToMountPositionX();
}

void MountBase::onInteract(PlatformerEntity* interactingEntity)
{
	super::onInteract(interactingEntity);

	this->mount(interactingEntity);
}
	
void MountBase::mount(PlatformerEntity* interactingEntity)
{
	if (this->mountedEntity != nullptr && interactingEntity == nullptr)
	{
		return;
	}

	interactingEntity->watchForAttachedBehavior<EntityMountBehavior>([=](EntityMountBehavior* entityMountBehavior)
	{
		if (entityMountBehavior->mount(this))
		{
			this->setInteractType(InteractObject::InteractType::None);
			this->mountedEntity = interactingEntity;

			this->setToMountPosition();
		}
	});
}

void MountBase::dismount()
{
	if (this->mountedEntity == nullptr)
	{
		return;
	}

	this->mountedEntity->watchForAttachedBehavior<EntityMountBehavior>([=](EntityMountBehavior* entityMountBehavior)
	{
		if (entityMountBehavior->dismount())
		{
			this->mountedEntity = nullptr;
			this->setInteractType(InteractObject::InteractType::Input);
		}
	});
}

void MountBase::setToMountPositionX()
{
	if (this->mountedEntity == nullptr)
	{
		return;
	}

	this->mountedEntity->setPositionX(this->getReparentPosition().x);
}

void MountBase::setToMountPosition()
{
	if (this->mountedEntity == nullptr)
	{
		return;
	}

	this->mountedEntity->setPosition(this->getReparentPosition());
}
