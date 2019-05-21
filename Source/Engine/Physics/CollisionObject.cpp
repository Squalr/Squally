#include "CollisionObject.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCValue.h"
#include "cocos/physics/CCPhysicsBody.h"
#include "cocos/physics/CCPhysicsContact.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

const std::string CollisionObject::MapKeyTypeCollision = "collision";
std::map<int, int> CollisionObject::InverseCollisionMap = std::map<int, int>();

const float CollisionObject::DefaultMaxHorizontalSpeed = 600.0f;
const float CollisionObject::DefaultMaxLaunchSpeed = 720.0f;
const float CollisionObject::DefaultMaxFallSpeed = -480.0f;
const float CollisionObject::DefaultHorizontalDampening = 0.75f;
const float CollisionObject::DefaultVerticalDampening = 1.0f;

CollisionObject* CollisionObject::create(cocos2d::PhysicsBody* physicsBody, CollisionType collisionType, bool isDynamic, bool canRotate)
{
	ValueMap valueMap = ValueMap();

	CollisionObject* instance = new CollisionObject(valueMap, physicsBody, collisionType, isDynamic, canRotate);

	instance->autorelease();

	return instance;
}

CollisionObject::CollisionObject(const ValueMap& initProperties, PhysicsBody* initPhysicsBody, std::string deserializedCollisionName, bool isDynamic, bool canRotate) :
	CollisionObject(initProperties, initPhysicsBody, (CollisionType)0, isDynamic, canRotate)
{
	// Fire event, allowing for the game to map the deserialized collision string type (ie 'solid') to a unique integer identifier for CollisionType
	CollisionMappingEvents::requestCollisionMapKeyMapping(CollisionMappingEvents::CollisionMapRequestArgs(deserializedCollisionName, this));
}

CollisionObject::CollisionObject(const ValueMap& initProperties, PhysicsBody* initPhysicsBody, CollisionType collisionType, bool isDynamic, bool canRotate) :
	super(initProperties)
{
	this->physicsBody = initPhysicsBody;
	this->collisionEvents = std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>>();
	this->collisionEndEvents = std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>>();
	this->currentCollisions = std::set<CollisionObject*>();
	this->physicsEnabled = true;
	this->bindTarget = nullptr;
	this->forceBindTarget = nullptr;
	this->forceBounceFactor = 0.0f;
	this->contactUpdateCallback = nullptr;

	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setRotationEnable(canRotate);
		this->physicsBody->setDynamic(isDynamic);
		this->physicsBody->setContactTestBitmask(0);
		this->physicsBody->setCollisionBitmask(0);
		this->setPhysicsBody(this->physicsBody);
	}

	this->setCollisionType(collisionType);
	this->setHorizontalDampening(CollisionObject::DefaultHorizontalDampening);
	this->setVerticalDampening(CollisionObject::DefaultVerticalDampening);
}

CollisionObject::~CollisionObject()
{
}

void CollisionObject::onEnter()
{
	super::onEnter();

	this->currentCollisions.clear();

	this->scheduleUpdate();
}

void CollisionObject::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->buildInverseCollisionMap();
}

void CollisionObject::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventCollisonMapUpdated, [=](EventCustom* eventCustom)
	{
		this->buildInverseCollisionMap();
	}));
}

void CollisionObject::buildInverseCollisionMap()
{
	// Part of Box2D requires that both the colliders and collidees have their bitmasks set -- this is how we accomplish that
	if (this->physicsBody != nullptr)
	{
		if (CollisionObject::InverseCollisionMap.find(this->getCollisionType()) != CollisionObject::InverseCollisionMap.end())
		{
			int inverseTypes = InverseCollisionMap[this->getCollisionType()];

			this->physicsBody->setContactTestBitmask(this->physicsBody->getContactTestBitmask() | inverseTypes);
			this->physicsBody->setCollisionBitmask(this->physicsBody->getCollisionBitmask() | inverseTypes);
		}
	}
}

void CollisionObject::setCollisionType(CollisionType collisionType)
{
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setCategoryBitmask(collisionType);
	}
}

void CollisionObject::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 worldPos = GameUtils::getWorldCoords(this);
	Vec2 pos = this->getPosition();
	Vec2 deltaPos = pos - worldPos;
	Size STOP_PHYSICS_OFFSET = visibleSize / 2.0f;

	if (this->contactUpdateCallback != nullptr)
	{
		this->contactUpdateCallback(&this->currentCollisions, dt);
	}

	if (this->physicsBody != nullptr && this->physicsBody->isDynamic())
	{
		// Apply dampening
		Vec2 velocity = this->getVelocity();

		velocity.x *= this->horizontalDampening;
		velocity.y *= this->verticalDampening;

		this->setVelocity(velocity);

		// Bound physics objects to camera bounds
		Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

		if (pos.x > cameraPosition.x + visibleSize.width + STOP_PHYSICS_OFFSET.width ||
			pos.x < cameraPosition.x - STOP_PHYSICS_OFFSET.width ||
			pos.y > cameraPosition.y + visibleSize.height + STOP_PHYSICS_OFFSET.height ||
			pos.y < cameraPosition.y - STOP_PHYSICS_OFFSET.height)
		{
			// Bypass setter to force disable physics for this object
			//this->physicsBody->setEnabled(false);
		}
		else
		{
			// Use setter such that if physics was disabled for a reason other than being off-screen, we do not overwrite that
			this->setPhysicsEnabled(this->physicsEnabled);
		}

		Rect mapBounds = GameCamera::getInstance()->getBounds();

		if (worldPos.x < mapBounds.getMinX())
		{
			this->setPositionX(deltaPos.x + mapBounds.getMinX());
		}

		if (worldPos.x > mapBounds.getMaxX())
		{
			this->setPositionX(deltaPos.x + mapBounds.getMaxX());
		}

		if (worldPos.y < mapBounds.getMinY())
		{
			this->setPositionY(deltaPos.y + mapBounds.getMinY());
		}

		if (worldPos.y > mapBounds.getMaxY())
		{
			this->setPositionY(deltaPos.y + mapBounds.getMaxY());
		}
	}
}

void CollisionObject::updateBinds()
{
	if (this->bindTarget != nullptr)
	{
		Vec2 positionDelta = this->getPosition();
		
		if (positionDelta != Vec2::ZERO)
		{
			this->bindTarget->setPosition(this->bindTarget->getPosition() + positionDelta);

			this->setPosition(Vec2::ZERO);
		}
	}

	if (this->forceBindTarget != nullptr)
	{
		Vec2 positionDelta = this->getPosition();

		if (positionDelta != Vec2::ZERO)
		{
			this->forceBindTarget->setPosition(this->forceBindTarget->getPosition() + positionDelta * this->forceBounceFactor);

			this->setPosition(Vec2::ZERO);
			this->getPhysicsBody()->setVelocity(Vec2::ZERO);
		}
	}
}

void CollisionObject::setContactUpdateCallback(std::function<void(std::set<CollisionObject*>* currentCollisions, float dt)> contactUpdateCallback)
{
	this->contactUpdateCallback = contactUpdateCallback;
}

void CollisionObject::setPhysicsEnabled(bool enabled)
{
	this->physicsEnabled = enabled;

	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setEnabled(enabled);
	}
}

void CollisionObject::setGravityEnabled(bool isEnabled)
{
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setGravityEnable(isEnabled);
	}
}

void CollisionObject::setPosition(const cocos2d::Vec2& position)
{
	super::setPosition(position);

	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setPositionInterruptPhysics(Vec2::ZERO);
	}
}

Vec2 CollisionObject::getVelocity()
{
	return this->physicsBody == nullptr ? Vec2::ZERO : this->physicsBody->getVelocity();
}

void CollisionObject::setVelocity(Vec2 velocity)
{
	// Prevent fast speeds
	velocity.x = MathUtils::clamp(velocity.x, -CollisionObject::DefaultMaxHorizontalSpeed, CollisionObject::DefaultMaxHorizontalSpeed);
	velocity.y = MathUtils::clamp(velocity.y, CollisionObject::DefaultMaxFallSpeed, CollisionObject::DefaultMaxLaunchSpeed);

	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setVelocity(velocity);
	}
}

void CollisionObject::setVelocityX(float velocityX)
{
	this->setVelocity(Vec2(velocityX, this->getVelocity().y));
}

void CollisionObject::setVelocityY(float velocityY)
{
	this->setVelocity(Vec2(this->getVelocity().x, velocityY));
}

void CollisionObject::setAngularVelocity(float angularVelocity)
{
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setAngularVelocity(angularVelocity);
	}
}

void CollisionObject::setHorizontalDampening(float horizontalDampening)
{
	this->horizontalDampening =  MathUtils::clamp(horizontalDampening, 0.0f, 1.0f);
}

void CollisionObject::setVerticalDampening(float verticalDampening)
{
	this->verticalDampening =  MathUtils::clamp(verticalDampening, 0.0f, 1.0f);
}
	
CollisionType CollisionObject::getCollisionType()
{
	return this->physicsBody == nullptr ? (CollisionType)0 : (CollisionType)this->physicsBody->getCategoryBitmask();
}

std::set<CollisionObject*> CollisionObject::getCurrentCollisions()
{
	return this->currentCollisions;
}

void CollisionObject::addPhysicsShape(cocos2d::PhysicsShape* shape)
{
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->addShape(shape);
	}
}

void CollisionObject::bindTo(cocos2d::Node* bindTarget)
{
	this->bindTarget = bindTarget;
}

void CollisionObject::forceBindTo(cocos2d::Node* forceBindTarget, float forceBounceFactor)
{
	// Tragically, the `forceBounceFactor` parameter is a hack that prevents physicsbodies from overlapping. Use 0.0f to see how this is broken.
	// I can't seem to diagnose the underlying math issues, so this hack fix is fine enough by me.

	this->setGravityEnabled(false);
	this->forceBindTarget = forceBindTarget;
	this->forceBounceFactor = forceBounceFactor;
}

void CollisionObject::whenCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision)
{
	for (auto it = collisionTypes.begin(); it != collisionTypes.end(); it++)
	{
		CollisionType collisionType = *it;

		this->addCollisionEvent(collisionType, this->collisionEvents, onCollision);
	}
}

void CollisionObject::whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd)
{
	for (auto it = collisionTypes.begin(); it != collisionTypes.end(); it++)
	{
		CollisionType collisionType = *it;

		this->addCollisionEvent(collisionType, this->collisionEndEvents, onCollisionEnd);
	}
}

void CollisionObject::addCollisionEvent(CollisionType collisionType, std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>>& eventMap, std::function<CollisionResult(CollisionData)> onCollision)
{
	if (CollisionObject::InverseCollisionMap.find(collisionType) != CollisionObject::InverseCollisionMap.end())
	{
		CollisionObject::InverseCollisionMap[collisionType] = CollisionObject::InverseCollisionMap[collisionType] | this->getCollisionType();
	}
	else
	{
		CollisionObject::InverseCollisionMap[collisionType] = this->getCollisionType();
	}

	ObjectEvents::TriggerCollisionMapUpdated();

	if (eventMap.find(collisionType) == eventMap.end())
	{
		eventMap[collisionType] = std::vector<std::function<CollisionResult(CollisionData)>>();
	}

	eventMap[collisionType].push_back(onCollision);

	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setContactTestBitmask(this->physicsBody->getContactTestBitmask() | (int)collisionType);
		this->physicsBody->setCollisionBitmask(this->physicsBody->getCollisionBitmask() | (int)collisionType);
	}
}

bool CollisionObject::onContactBegin(PhysicsContact &contact)
{
	// Currently we are not distinguishing between begin/update
	return this->onContactUpdate(contact);
}

bool CollisionObject::onContactUpdate(PhysicsContact &contact)
{
	CollisionData collisionData = this->constructCollisionData(contact);

	this->currentCollisions.insert(collisionData.other);

	return this->runContactEvents(contact, this->collisionEvents, CollisionResult::CollideWithPhysics, collisionData);
}

bool CollisionObject::onContactEnd(PhysicsContact &contact)
{
	CollisionData collisionData = this->constructCollisionData(contact);

	if (this->currentCollisions.find(collisionData.other) != this->currentCollisions.end())
	{
		this->currentCollisions.erase(collisionData.other);
	}

	return this->runContactEvents(contact, this->collisionEndEvents, CollisionResult::DoNothing, collisionData);
}

bool CollisionObject::runContactEvents(cocos2d::PhysicsContact& contact, std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>>& eventMap, CollisionResult defaultResult, const CollisionData& collisionData)
{
	CollisionResult result = defaultResult;

	if (collisionData.other != nullptr)
	{
		CollisionType collisionType = collisionData.other->getCollisionType();

		if (eventMap.find(collisionType) != eventMap.end())
		{
			std::vector<std::function<CollisionResult(CollisionData)>> events = eventMap[collisionType];

			for (auto eventIt = events.begin(); eventIt != events.end(); eventIt++)
			{
				CollisionResult eventResult = (*eventIt)(collisionData);

				// Anti-default takes precidence
				result = (eventResult != defaultResult) ? eventResult : result;
			}
		}
	}
	
	this->updateBinds();

	return (result == CollisionResult::CollideWithPhysics ? true : false);
}

CollisionObject::CollisionData CollisionObject::constructCollisionData(PhysicsContact& contact)
{
	PhysicsShape* other = nullptr;

	if (contact.getShapeA()->getBody() != this->physicsBody && contact.getShapeB()->getBody() != this->physicsBody)
	{
		return nullptr;
	}

	if (contact.getShapeA()->getBody() == this->physicsBody)
	{
		other = contact.getShapeB();
	}
	else
	{
		other = contact.getShapeA();
	}

	return CollisionObject::CollisionData(dynamic_cast<CollisionObject*>(other->getBody()->getNode()));
}

void CollisionObject::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
	super::visit(renderer, parentTransform, parentFlags);

	this->updateBinds();
}
