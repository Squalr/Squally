#include "Collectable.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string Collectable::SaveKeyIsCollected = "is_collected";

Collectable* Collectable::create(ValueMap& initProperties)
{
	Collectable* instance = new Collectable(initProperties);

	instance->autorelease();

	return instance;
}

Collectable::Collectable(ValueMap& initProperties) : super(initProperties)
{
	this->collectableNode = Node::create();
	this->collectableCollision = CollisionObject::create(PhysicsBody::createBox(Size(64.0f, 64.0f)), (CollisionType)PlatformerCollisionType::Collectable, true, false);
	this->collectionEvents = std::vector<std::function<void()>>();
	this->isCollected = false;

	this->collectableCollision->addChild(this->collectableNode);
	this->addChild(this->collectableCollision);
}

Collectable::~Collectable()
{
}

void Collectable::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Collectable::initializePositions()
{
	super::initializePositions();
}

void Collectable::initializeListeners()
{
	super::initializeListeners();

	this->collectableCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough  }, [=](CollisionObject::CollisionData data)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->collectableCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::PlayerWeapon, (int)PlatformerCollisionType::PlayerHover }, [=](CollisionObject::CollisionData data)
	{
		if (!this->isCollected)
		{
			this->disableCollection();

			for (auto it = this->collectionEvents.begin(); it != this->collectionEvents.begin(); it++)
			{
				(*it)();
			}

			this->saveObjectState(Collectable::SaveKeyIsCollected, Value(true));
		}

		return CollisionObject::CollisionResult::DoNothing;
	});
}

void Collectable::onObjectStateLoaded()
{
	super::onObjectStateLoaded();

	if (this->getObjectStateOrDefault(Collectable::SaveKeyIsCollected, Value(false)).asBool())
	{
		this->disableCollection();
	}
}

void Collectable::onCollected(std::function<void()> onCollectedEvent)
{
	this->collectionEvents.push_back(onCollectedEvent);
}

void Collectable::disableCollection()
{
	this->isCollected = true;
	this->collectableCollision->setPhysicsEnabled(false);
	this->collectableCollision->setVisible(false);
}
