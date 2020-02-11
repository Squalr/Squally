#include "CollisionObject.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCValue.h"
#include "cocos/physics/CCPhysicsBody.h"
#include "cocos/physics/CCPhysicsContact.h"
#include "cocos/physics/CCPhysicsWorld.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "cocos/physics/chipmunk/chipmunk_private.h"

using namespace cocos2d;

const std::string CollisionObject::MapKeyTypeCollision = "collision";
const std::string CollisionObject::MapKeyCollisionTypeNone = "none";
const std::string CollisionObject::MapKeyFriction = "friction";
std::map<int, int> CollisionObject::InverseCollisionMap = std::map<int, int>();

const float CollisionObject::DefaultMaxHorizontalSpeed = 600.0f;
const float CollisionObject::DefaultMaxLaunchSpeed = 720.0f;
const float CollisionObject::DefaultMaxFallSpeed = -480.0f;
const float CollisionObject::DefaultHorizontalDampening = 0.75f;
const float CollisionObject::DefaultVerticalDampening = 1.0f;
const float CollisionObject::CollisionZThreshold = 20.0f;

CollisionObject* CollisionObject::create(const ValueMap& properties, PhysicsBody* physicsBody, CollisionType collisionType, bool isDynamic, bool canRotate)
{
	CollisionObject* instance = new CollisionObject(properties, physicsBody, collisionType, isDynamic, canRotate);

	instance->autorelease();

	return instance;
}

CollisionObject* CollisionObject::create(const ValueMap& properties, PhysicsBody* physicsBody, std::string collisionName, bool isDynamic, bool canRotate)
{
	CollisionObject* instance = CollisionObject::create(properties, physicsBody, (CollisionType)0, isDynamic, canRotate);

	// Fire event, allowing for the game to map the deserialized collision string type (ie 'solid') to a unique integer identifier for CollisionType
	CollisionMappingEvents::requestCollisionMapKeyMapping(CollisionMappingEvents::CollisionMapRequestArgs(collisionName, instance));

	return instance;
}

CollisionObject* CollisionObject::create(PhysicsBody* physicsBody, CollisionType collisionType, bool isDynamic, bool canRotate)
{
	ValueMap valueMap = ValueMap();

	return CollisionObject::create(valueMap, physicsBody, collisionType, isDynamic, canRotate);
}

CollisionObject* CollisionObject::create(PhysicsBody* physicsBody, std::string collisionName, bool isDynamic, bool canRotate)
{
	ValueMap valueMap = ValueMap();

	return CollisionObject::create(valueMap, physicsBody, collisionName, isDynamic, canRotate);
}

CollisionObject::CollisionObject(const ValueMap& properties, PhysicsBody* initPhysicsBody, std::string deserializedCollisionName, bool isDynamic, bool canRotate) :
	CollisionObject(properties, initPhysicsBody, (CollisionType)0, isDynamic, canRotate)
{
}

CollisionObject::CollisionObject(const ValueMap& properties, PhysicsBody* initPhysicsBody, CollisionType collisionType, bool isDynamic, bool canRotate) :
	super(properties)
{
	this->physicsBody = initPhysicsBody;
	this->collisionEvents = std::map<CollisionType, std::vector<CollisionEvent>>();
	this->collisionEndEvents = std::map<CollisionType, std::vector<CollisionEvent>>();
	this->currentCollisions = std::vector<CollisionObject*>();
	this->passThroughCandidates = std::map<CollisionObject*, CollisionData>();
	this->passThroughCandidatesIter = std::map<CollisionObject*, CollisionData>();
	this->gravityEnabled = true;
	this->gravityInversed = true;
	this->contactUpdateCallback = nullptr;
	this->onDebugPositionSet = nullptr;
	this->bindTarget = nullptr;
	this->debugDrawNode = nullptr;
	this->debugInfoSpawned = false;

	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setGravityEnable(false);
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

	// Optimization: do not add during initalizeListeners to avoid extra calls
	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventCollisonMapUpdated, [=](EventCustom* eventCustom)
	{
		this->buildInverseCollisionMap();
	}));
}

void CollisionObject::initializeListeners()
{
	super::initializeListeners();
}

void CollisionObject::despawn()
{
	super::despawn();
	
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setEnabled(false);
	}
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
	super::update(dt);

	if (this->contactUpdateCallback != nullptr && !this->currentCollisions.empty())
	{
		this->contactUpdateCallback(this->currentCollisions, dt);
	}

	// Retry collision on objects that are not in the same depth, as they may have moved through z-space (cocos/chipmunk do not handle this automatically)
	if (!this->passThroughCandidates.empty())
	{
		this->passThroughCandidatesIter = this->passThroughCandidates;
		
		for (auto candidate : this->passThroughCandidatesIter)
		{
			this->onContactRetry(candidate.second);
		}
	}

	if (this->physicsBody != nullptr && this->physicsBody->isDynamic())
	{
		Vec2 velocity = this->getVelocity();
		Scene* scene = Director::getInstance()->getRunningScene();

		// Apply gravity
		if (this->gravityEnabled && scene != nullptr && scene->getPhysicsWorld() != nullptr)
		{
			const Vec2 gravity = Director::getInstance()->getRunningScene()->getPhysicsWorld()->getGravity();

			velocity.x += gravity.x * dt;

			if (this->gravityInversed)
			{
				velocity.y += gravity.y * dt;
			}
			else
			{
				velocity.y -= gravity.y * dt;
			}
		}

		// Apply dampening
		velocity.x *= this->horizontalDampening;
		velocity.y *= this->verticalDampening;

		this->setVelocity(velocity);
	}
}

void CollisionObject::setContactUpdateCallback(std::function<void(const std::vector<CollisionObject*>& currentCollisions, float dt)> contactUpdateCallback)
{
	this->contactUpdateCallback = contactUpdateCallback;
}

void CollisionObject::setPhysicsEnabled(bool enabled)
{
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setEnabled(enabled);
	}
}

void CollisionObject::setGravityEnabled(bool isEnabled)
{
	this->gravityEnabled = isEnabled;
}

void CollisionObject::inverseGravity()
{
	this->gravityInversed = !this->gravityInversed;
}

void CollisionObject::setPosition(const Vec2& position)
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

std::vector<CollisionObject*> CollisionObject::getCurrentCollisions()
{
	return this->currentCollisions;
}

bool CollisionObject::isCollidingWith(CollisionObject* collisionObject)
{
	return std::find(this->currentCollisions.begin(), this->currentCollisions.end(), collisionObject) != this->currentCollisions.end();
}

void CollisionObject::addPhysicsShape(PhysicsShape* shape)
{
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->addShape(shape);
	}
}

void CollisionObject::bindTo(GameObject* bindTarget)
{
	this->bindTarget = bindTarget;

	if (this->bindTarget != nullptr && this->bindTarget->getParent() != nullptr)
	{
		GameUtils::changeParent(this, this->bindTarget->getParent(), true);
		this->setPosition(bindTarget->getPosition());
	}
}

void CollisionObject::unbind()
{
	this->bindTarget = nullptr;
}

void CollisionObject::whenCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision)
{
	for (auto it = collisionTypes.begin(); it != collisionTypes.end(); it++)
	{
		CollisionType collisionType = *it;

		this->addCollisionEvent(collisionType, this->collisionEvents, CollisionEvent(onCollision));
	}
}

void CollisionObject::whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd)
{
	for (auto it = collisionTypes.begin(); it != collisionTypes.end(); it++)
	{
		CollisionType collisionType = *it;

		this->addCollisionEvent(collisionType, this->collisionEndEvents, CollisionEvent(onCollisionEnd));
	}
}

void CollisionObject::addCollisionEvent(CollisionType collisionType, std::map<CollisionType, std::vector<CollisionEvent>>& eventMap, CollisionEvent onCollision)
{
	if (CollisionObject::InverseCollisionMap.find(collisionType) != CollisionObject::InverseCollisionMap.end())
	{
		int newBitmask = CollisionObject::InverseCollisionMap[collisionType] | this->getCollisionType();

		if (CollisionObject::InverseCollisionMap[collisionType] != newBitmask)
		{
			CollisionObject::InverseCollisionMap[collisionType] = newBitmask;
			
			ObjectEvents::TriggerCollisionMapUpdated();
		}
	}
	else
	{
		CollisionObject::InverseCollisionMap[collisionType] = this->getCollisionType();

		ObjectEvents::TriggerCollisionMapUpdated();
	}

	if (eventMap.find(collisionType) == eventMap.end())
	{
		eventMap[collisionType] = std::vector<CollisionEvent>();
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

	if (!this->isWithinZThreshold(collisionData))
	{
		this->passThroughCandidates[collisionData.other] = collisionData;
		return false;
	}
	
	if (std::find(this->currentCollisions.begin(), this->currentCollisions.end(), collisionData.other) == this->currentCollisions.end())
	{
		this->currentCollisions.push_back(collisionData.other);
	}

	return this->runContactEvents(this->collisionEvents, CollisionResult::CollideWithPhysics, collisionData);
}

bool CollisionObject::onContactRetry(CollisionData& collisionData)
{
	if (!this->isWithinZThreshold(collisionData))
	{
		return false;
	}
	
	if (std::find(this->currentCollisions.begin(), this->currentCollisions.end(), collisionData.other) == this->currentCollisions.end())
	{
		this->currentCollisions.push_back(collisionData.other);
	}

	this->runContactEvents(this->collisionEvents, CollisionResult::CollideWithPhysics, collisionData);

	return true;
}

bool CollisionObject::onContactEnd(PhysicsContact &contact)
{
	CollisionData collisionData = this->constructCollisionData(contact);

	if (this->passThroughCandidates.find(collisionData.other) != this->passThroughCandidates.end())
	{
		this->passThroughCandidates.erase(collisionData.other);
	}

	this->currentCollisions.erase(
		std::remove(this->currentCollisions.begin(), this->currentCollisions.end(), collisionData.other), this->currentCollisions.end()
	);

	if (!this->isWithinZThreshold(collisionData))
	{
		return false;
	}

	return this->runContactEvents(this->collisionEndEvents, CollisionResult::DoNothing, collisionData);
}

void CollisionObject::ClearInverseMap()
{
	CollisionObject::InverseCollisionMap.clear();
}

PhysicsBody* CollisionObject::createCapsulePolygon(cocos2d::Size size, float scale, float capsuleRadius, float friction)
{
	cocos2d::Size newSize = size * scale;

	newSize.height = std::max(0.0f, newSize.height - capsuleRadius * 2.0f);

	std::vector<Vec2> points = std::vector<Vec2>();

	// Right side
	points.push_back(Vec2(newSize.width / 2.0f, newSize.height / 2.0f));
	points.push_back(Vec2(newSize.width / 2.0f, -newSize.height / 2.0f));

	// Bottom capsule
	points.push_back(Vec2(0.0f, -newSize.height / 2.0f - capsuleRadius));

	// Left side
	points.push_back(Vec2(-newSize.width / 2.0f, -newSize.height / 2.0f));
	points.push_back(Vec2(-newSize.width / 2.0f, newSize.height / 2.0f));

	// Top capsule
	points.push_back(Vec2(0.0f, newSize.height / 2.0f + capsuleRadius));

	return PhysicsBody::createPolygon(points.data(), points.size(), PhysicsMaterial(0.5f, 0.0f, friction));
}

bool CollisionObject::runContactEvents(std::map<CollisionType, std::vector<CollisionEvent>>& eventMap, CollisionResult defaultResult, const CollisionData& collisionData)
{
	if (this->physicsBody != nullptr && !this->physicsBody->isEnabled())
	{
		return false;
	}

	CollisionResult result = defaultResult;

	if (collisionData.other != nullptr && this->isWithinZThreshold(collisionData))
	{
		CollisionType collisionType = collisionData.other->getCollisionType();

		if (eventMap.find(collisionType) != eventMap.end())
		{
			std::vector<CollisionEvent> events = eventMap[collisionType];

			for (auto eventIt = events.begin(); eventIt != events.end(); eventIt++)
			{
				CollisionResult eventResult = (*eventIt).collisionEvent(collisionData);

				// Anti-default takes precidence
				result = (eventResult != defaultResult) ? eventResult : result;
			}
		}
	}

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
	this->updateBinds();

	super::visit(renderer, parentTransform, parentFlags);

	if (this->debugDrawNode != nullptr)
	{
        this->debugDrawNode->clear();
	}

	if (DeveloperModeController::getDebugLevel() > 0 && this->physicsBody != nullptr)
	{
		if (!this->debugInfoSpawned)
		{
			this->debugInfoSpawned = true;
			this->debugDrawNode = DrawNode::create();

			ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
				this,
				this->debugDrawNode,
				ObjectEvents::SpawnMethod::TopMost,
				ObjectEvents::PositionMode::Discard,
				[&]()
				{
				},
				[&]()
				{
					this->debugDrawNode = nullptr;
				}));
		}

		if (this->debugDrawNode  != nullptr)
		{
			this->debugDrawNode->setPositionZ(GameUtils::getDepth(this));
			PhysicsWorld::debugDrawBody(this->physicsBody, this->debugDrawNode, Vec2::ZERO);
		}
	}
}

void CollisionObject::updateBinds()
{
	if (this->bindTarget != nullptr)
	{
		if (this->bindTarget->isDespawned())
		{
			this->unbind();
			this->despawn();
		}
		else
		{
			this->bindTarget->setPosition(this->getPosition());
		}
	}
}

bool CollisionObject::isWithinZThreshold(const CollisionData& collisionData)
{
	const float thisDepth = GameUtils::getDepth(this);
	const float otherDepth = GameUtils::getDepth(collisionData.other);

	if (std::abs(thisDepth - otherDepth) >= CollisionObject::CollisionZThreshold)
	{
		return false;
	}

	return true;
}
