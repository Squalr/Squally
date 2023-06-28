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
	this->rootNode = Node::create();
	this->reparentNode = Node::create();
	this->frontNode = Node::create();
	
	this->rootNode->addChild(this->reparentNode);
	this->rootNode->addChild(this->frontNode);
	this->addChild(this->rootNode);
}

MountBase::~MountBase()
{
}

Node* MountBase::getReparentNode()
{
	return this->reparentNode;
}

Vec2 MountBase::getReparentPosition(PlatformerEntity* entity)
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
		for (PlatformerEntity* mountedEntity : this->mountedEntities)
		{
			if (mountedEntity != nullptr)
			{
				mountedEntity->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
				{
					healthBehavior->setHealth(0, true);
				});
			}
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
	if (interactingEntity == nullptr || this->mountedEntities.find(interactingEntity) != this->mountedEntities.end())
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
			this->mountedEntities.insert(interactingEntity);

			this->setToMountPosition();
		}
	});
}

void MountBase::dismount(PlatformerEntity* entity)
{
	if (this->mountedEntities.find(entity) == this->mountedEntities.end())
	{
		return;
	}

	entity->watchForComponent<EntityCollisionBehaviorBase>([=](EntityCollisionBehaviorBase* entityCollisionBehavior)
	{
		entityCollisionBehavior->setMountPhysics(false);
	});

	entity->watchForComponent<EntityMountBehavior>([=](EntityMountBehavior* entityMountBehavior)
	{
		if (entityMountBehavior->dismount())
		{
			this->mountedEntities.erase(entity);
			this->setInteractType(InteractObject::InteractType::Input);
		}
	});
}

void MountBase::dismountAll()
{
	std::set<PlatformerEntity*> mountedEntitesCopy = this->mountedEntities;

	for (PlatformerEntity* mountedEntity : mountedEntitesCopy)
	{
		this->dismount(mountedEntity);
	}
}

bool MountBase::isMounted() const
{
	return this->mountedEntities.size() > 0;
}

bool MountBase::isTargetMounted(PlatformerEntity* entity) const
{
	return this->mountedEntities.find(entity) != this->mountedEntities.end();
}

void MountBase::setToMountPositionX()
{
	for (PlatformerEntity* mountedEntity : this->mountedEntities)
	{
		if (mountedEntity == nullptr)
		{
			mountedEntity->setPositionX(this->getReparentPosition(mountedEntity).x);
		}
	}
}

void MountBase::setToMountPosition()
{
	for (PlatformerEntity* mountedEntity : this->mountedEntities)
	{
		if (mountedEntity != nullptr)
		{
			mountedEntity->setPosition(this->getReparentPosition(mountedEntity));
		}
	}
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
	for (PlatformerEntity* mountedEntity : this->mountedEntities)
	{
		if (mountedEntity != nullptr)
		{
			switch(this->mountDirection)
			{
				case MountDirection::Left:
				{
					mountedEntity->getAnimations()->setFlippedX(true);
					break;
				}
				case MountDirection::Right:
				{
					mountedEntity->getAnimations()->setFlippedX(false);
					break;
				}
				case MountDirection::None:
				default:
				{
					break;
				}
			}
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

