#include "MountBase.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/ItemPools/RecipePools/RecipePoolDeserializer.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityCollisionBehaviorBase.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMountBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string MountBase::PropertyDirection = "direction";
const std::string MountBase::PropertySpeed = "speed";

MountBase::MountBase(ValueMap& properties, CSize size, bool updateXOnly) : super(properties, InteractObject::InteractType::Input, size)
{
	this->updateXOnly = updateXOnly;
	this->reparentNode = Node::create();
	this->frontNode = Node::create();
	
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

void MountBase::initializeListeners()
{
	super::initializeListeners();

	this->interactCollision->whenCollidesWith({ (CollisionType)PlatformerCollisionType::Damage }, [=](CollisionData collisionData)
	{
		if (this->mountedEntity != nullptr)
		{
			this->mountedEntity->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
			{
				healthBehavior->setHealth(0, true);
			});
		}

		return CollisionResult::DoNothing;
	});
}

void MountBase::update(float dt)
{
	super::update(dt);

	if (this->updateXOnly)
	{
		this->setToMountPositionX();
	}
	else
	{
		this->setToMountPosition();
	}
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

	interactingEntity->watchForComponent<EntityCollisionBehaviorBase>([=](EntityCollisionBehaviorBase* entityCollisionBehavior)
	{
		entityCollisionBehavior->setMountPhysics(true);
	});

	interactingEntity->watchForComponent<EntityMountBehavior>([=](EntityMountBehavior* entityMountBehavior)
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

	this->mountedEntity->watchForComponent<EntityCollisionBehaviorBase>([=](EntityCollisionBehaviorBase* entityCollisionBehavior)
	{
		entityCollisionBehavior->setMountPhysics(false);
	});

	this->mountedEntity->watchForComponent<EntityMountBehavior>([=](EntityMountBehavior* entityMountBehavior)
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

void MountBase::moveMount(float dt)
{
	if (!this->isMoving || !this->canMoveOverride)
	{
		return;
	}

	switch(this->mountDirection)
	{
		case MountDirection::Left:
		{
			this->setPosition(this->getPosition() - Vec2(this->mountSpeed * dt, 0.0f));
			break;
		}
		default:
		case MountDirection::Right:
		{
			this->setPosition(this->getPosition() + Vec2(this->mountSpeed * dt, 0.0f));
			break;
		}
	}
}

void MountBase::faceEntityTowardsDirection()
{
	if (this->mountedEntity == nullptr)
	{
		return;
	}

	switch(this->mountDirection)
	{
		case MountDirection::Left:
		{
			this->mountedEntity->getAnimations()->setFlippedX(true);
			break;
		}
		default:
		case MountDirection::Right:
		{
			this->mountedEntity->getAnimations()->setFlippedX(false);
			break;
		}
	}
}

void MountBase::setMountDirection(MountDirection mountDirection)
{
	this->mountDirection = mountDirection;
}

void MountBase::reverse()
{
	switch(this->mountDirection)
	{
		case MountDirection::Left:
		{
			this->setMountDirection(MountDirection::Right);
			break;
		}
		default:
		case MountDirection::Right:
		{
			this->setMountDirection(MountDirection::Left);
			break;
		}
	}
}

void MountBase::parseDirection()
{
	std::string direction = GameUtils::getKeyOrDefault(this->properties, MountBase::PropertyDirection, Value("")).asString();

	if (direction == "left")
	{
		this->mountDirection = MountDirection::Left;
	}
	else
	{
		this->mountDirection = MountDirection::Right;
	}
}

