#include "EntityGroundCollisionBehavior.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EnginePhysicsTypes.h"
#include "Engine/Terrain/TerrainObject.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityHoverCollisionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Petrification/EntityPetrificationBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityGroundCollisionBehavior::MapKey = "entity-ground-collisions";
const int EntityGroundCollisionBehavior::DropShadowDetectorCount = 5;
const float EntityGroundCollisionBehavior::DropShadowPadding = 32.0f;
const float EntityGroundCollisionBehavior::DropShadowCollisionHeight = 512.0f;
const float EntityGroundCollisionBehavior::GroundCollisionPadding = -4.0f;
const float EntityGroundCollisionBehavior::GroundCollisionOffset = 0.0f;
const float EntityGroundCollisionBehavior::GroundCollisionHeight = 32.0f;

EntityGroundCollisionBehavior* EntityGroundCollisionBehavior::create(GameObject* owner)
{
	EntityGroundCollisionBehavior* instance = new EntityGroundCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityGroundCollisionBehavior::EntityGroundCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->dropShadowCollisions = std::vector<CollisionObject*>();
	this->groundCollision = nullptr;
	this->detectorWidth = 0.0f;
	this->hoverCollisionBehavior = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->detectorWidth = std::max((this->entity->getEntitySize()).width + EntityGroundCollisionBehavior::GroundCollisionPadding * 2.0f, 8.0f);
	}

	this->toggleQueryable(false);
}

EntityGroundCollisionBehavior::~EntityGroundCollisionBehavior()
{
}

void EntityGroundCollisionBehavior::onLoad()
{
	this->entity->watchForComponent<EntityHoverCollisionBehavior>([=](EntityHoverCollisionBehavior* hoverCollisionBehavior)
	{
		this->hoverCollisionBehavior = hoverCollisionBehavior;
	});

	this->defer([=]()
	{
		this->buildDropShadowCollisionDetector();
		this->buildGroundCollisionDetector();
		this->toggleQueryable(true);
		this->scheduleUpdate();
	});
}

void EntityGroundCollisionBehavior::onDisable()
{
	super::onDisable();
	
	for (CollisionObject* dropShadowCollision : this->dropShadowCollisions)
	{
		if (dropShadowCollision != nullptr)
		{
			dropShadowCollision->setPhysicsFlagEnabled(false);
		}
	}
	
	if (this->groundCollision != nullptr)
	{
		this->groundCollision->setPhysicsFlagEnabled(false);
	}
}

void EntityGroundCollisionBehavior::update(float dt)
{
	super::update(dt);

	CollisionObject* groundCollider = this->getGroundCollision();
	Sprite* dropShadow = this->entity->getDropShadow();

	auto tryCastShadow = [&](CollisionObject* dropShadowCollision, CollisionObject* candidateGround)
	{
		DropShadowResult result;

		if (candidateGround == nullptr)
		{
			return result;
		}

		const std::vector<Vec2>& points = candidateGround->getPoints();

		switch (candidateGround->getShape())
		{
			case CollisionShape::Segment:
			{
				if (points.size() >= 2)
				{
					Vec2 dropShadowPosition = dropShadowCollision->getCachedWorldCoords();
					Vec2 groundPosition = candidateGround->getCachedWorldCoords();
					Vec2 dropShadowSource = std::get<0>(dropShadowCollision->getSegmentsRotated()[0]);
					Vec2 dropShadowDest = std::get<1>(dropShadowCollision->getSegmentsRotated()[0]);
					Vec2 groundSource = std::get<0>(candidateGround->getSegmentsRotated()[0]);
					Vec2 groundDest = std::get<1>(candidateGround->getSegmentsRotated()[0]);
					std::tuple<Vec2, Vec2> dropShadowSegment = std::make_tuple(dropShadowPosition + dropShadowSource, dropShadowPosition + dropShadowDest);
					std::tuple<Vec2, Vec2> groundSegment = std::make_tuple(groundPosition + groundSource, groundPosition + groundDest);
					
					if (AlgoUtils::doSegmentsIntersect(dropShadowSegment, groundSegment))
					{
						Vec2 intersectionPoint = AlgoUtils::getLineIntersectionPoint(dropShadowSegment, groundSegment);

						float verticalDistance = intersectionPoint.y - (dropShadowPosition.y + dropShadowSource.y);

						float xDelta = (groundDest.x - groundSource.x);
						float yDelta = (groundDest.y - groundSource.y);
						float slope = xDelta == 0.0f ? 1.0f : -(yDelta / xDelta);
						
						result.isValid = true;
						result.slope = slope;
						result.dropDistance = verticalDistance / EntityGroundCollisionBehavior::DropShadowCollisionHeight;
						result.intersectionPoint = intersectionPoint;

						return result;
					}
				}
				break;
			}
			default:
			{
				break;
			}
		}

		return result;
	};

	std::vector<DropShadowResult> results;

	// Algorithm is to iterate over each drop shadow line, take the highest valid point of all of their collisions, then average their angle
	for (CollisionObject* dropShadowCollision : this->dropShadowCollisions)
	{
		if (dropShadowCollision == nullptr)
		{
			continue;
		}

		DropShadowResult acceptedResult;

		for (CollisionObject* candidateGround : dropShadowCollision->getCurrentCollisions())
		{
			DropShadowResult nextResult = tryCastShadow(dropShadowCollision, candidateGround);

			if (nextResult.isValid)
			{
				if (std::abs(nextResult.slope) > M_PI / 2)
				{
					continue;
				}

				if (!acceptedResult.isValid || nextResult.intersectionPoint.y > acceptedResult.intersectionPoint.y)
				{
					acceptedResult = nextResult;
				}
			}
		}

		if (acceptedResult.isValid)
		{
			results.push_back(acceptedResult);
		}
	}

	int resultCount = (int)results.size();
	float averageNormalizedDistance = 0.0f;
	float averageSlope = 0.0f;
	Vec2 centerIntersection = Vec2::ZERO;

	if (resultCount > 0)
	{
		centerIntersection = resultCount % 2 == 1
			? results[resultCount / 2].intersectionPoint
			: ((results[resultCount / 2 - 1].intersectionPoint + results[resultCount / 2].intersectionPoint) / 2);

		for (DropShadowResult& result : results)
		{
			averageNormalizedDistance += result.dropDistance / float(resultCount);
			averageSlope += result.slope / float(resultCount);
		}
	}

	// Dead animations should cast larger shadows due to the corpse generally spreading over more area
	const float DeathScalerSpeed = 3.0f;
	const float MaxDeathScale = 1.75f;

	// An exception for petrified entities, which are also marked as dead as a shitty hack
	bool isPetrified = false;

	this->entity->getComponent<EntityPetrificationBehavior>([&](EntityPetrificationBehavior* behavior)
	{
		isPetrified = !behavior->isCured();
	});

	if (!isPetrified && !this->entity->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
	{
		this->deathScaler = MathUtils::clamp(this->deathScaler + dt * DeathScalerSpeed, 1.0f, MaxDeathScale);
	}
	else
	{
		this->deathScaler = MathUtils::clamp(this->deathScaler - dt * DeathScalerSpeed, 1.0f, MaxDeathScale);
	}

	float massMultiplier = MathUtils::clamp(this->entity->getEntitySize().width / 128.0f, 0.75f, 4.0f);
	const float DefaultScale = 0.33f;
	float resultScale = MathUtils::clamp(averageNormalizedDistance * this->deathScaler * massMultiplier * DefaultScale, 0.0f, 1.0f);
	float upScale = resultScale / DefaultScale;

	dropShadow->setScale(resultScale);
	dropShadow->setOpacity((GLubyte)(averageNormalizedDistance * 255.0f));
	dropShadow->setRotation(averageSlope * 180.0f / float(M_PI));
	
	const float VisualAdjustment = 0.0f;
	float shadowHeight = dropShadow->getContentSize().height;

	// Adjust drop shadow Y to fall onto the segment below. Zero out the X since we want it centered.
	GameUtils::setWorldCoords(dropShadow, Vec2(centerIntersection.x, centerIntersection.y - shadowHeight * upScale / 2.0f));
	dropShadow->setPositionX(0.0f);
}

CollisionObject* EntityGroundCollisionBehavior::getGroundCollision()
{
	return this->groundCollision;
}

void EntityGroundCollisionBehavior::onCollideWithGround()
{
	// Clear current animation
	if (this->entity->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true) && this->entity->getRuntimeStateOrDefaultFloat(StateKeys::VelocityY, 0.0f) <= 0.0f)
	{
		if (this->entity->getAnimations()->getCurrentAnimation() == "Jump")
		{
			this->entity->getAnimations()->clearAnimationPriority();
		}

		this->entity->getAnimations()->playAnimation();
	}
}

bool EntityGroundCollisionBehavior::isOnGround()
{
	if (this->groundCollision == nullptr || !this->groundCollision->hasCollisions())
	{
		return false;
	}

	static const float ToleranceDegrees = 10.0f;

	// Now check the normal angles of each thing the ground collider is hitting to make sure they actually are reasonable.
	for (CollisionObject* next : this->groundCollision->getCurrentCollisions())
	{
		// For non-segments (which are very rare shapes), we can't really check normals, so just say we're on the ground.
		if (next->getShape() != CollisionShape::Segment || (int)next->getPoints().size() < 2)
		{
			return true;
		}

		Vec2 delta = next->getPoints()[0] - next->getPoints()[1];

		if (delta.x == 0.0f && delta.y == 0.0f)
		{
			continue;
		}

		// Absolute value the deltas to force the first quadrant of unit circle (ie in the 0.0f to 90.0f range)
		float angle = std::atan2(std::abs(delta.y), std::abs(delta.x));
		float angleDegrees = angle * (180.0f / float(M_PI));

		// The slope is considered ground if within the tolerance
		if (angleDegrees < 90.0f - ToleranceDegrees)
		{
			return true;
		}
	}

	return false;
}

bool EntityGroundCollisionBehavior::isStandingOn(CollisionObject* collisonObject)
{
	if (this->groundCollision == nullptr)
	{
		return false;
	}

	Node* currentCollisionGroup = collisonObject->getParent();

	for (CollisionObject* next : this->groundCollision->getCurrentCollisions())
	{
		if (next->hasCollisionType(CollisionType(PlatformerCollisionType::Solid))
			|| next->hasCollisionType(CollisionType(PlatformerCollisionType::PassThrough)))
		{
			// Do a parent check because multiple collison objects can be nested under the same macro-object (ie terrain segments)
			if (next->getParent() == currentCollisionGroup)
			{
				return true;
			}
		}
	}

	return false;
}

bool EntityGroundCollisionBehavior::isStandingOnSomethingOtherThan(CollisionObject* collisonObject)
{
	if (this->groundCollision == nullptr)
	{
		return false;
	}

	Node* currentCollisionGroup = collisonObject->getParent();

	// Greedy search for the oldest collision. This works out as being the object that is the true "ground".
	for (CollisionObject* next : this->groundCollision->getCurrentCollisions())
	{
		const Node* otherCollisionGroup = next->getParent();

		if (next->hasCollisionType(CollisionType(PlatformerCollisionType::Solid))
			|| next->hasCollisionType(CollisionType(PlatformerCollisionType::PassThrough)))
		{
			// Do a parent check because multiple collison objects can be nested under the same macro-object (ie terrain segments)
			if (otherCollisionGroup != currentCollisionGroup)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}

void EntityGroundCollisionBehavior::buildDropShadowCollisionDetector()
{
	if (!this->dropShadowCollisions.empty())
	{
		return;
	}

	float countAsFloat = float(EntityGroundCollisionBehavior::DropShadowDetectorCount);

	for (int index = 0; index < EntityGroundCollisionBehavior::DropShadowDetectorCount; index++)
	{
		CollisionObject* dropShadowCollision = CollisionObject::create(
			CollisionObject::createSegmentY(EntityGroundCollisionBehavior::DropShadowCollisionHeight),
			(int)PlatformerCollisionType::GroundDetector,
			CollisionObject::Properties(false, false),
			Color4F::GREEN
		);
		
		float spacing = this->detectorWidth / countAsFloat;
		float x = ((float)index - countAsFloat / 2.0f) * spacing + spacing / 2.0f;

		dropShadowCollision->setPosition(Vec2(x, EntityGroundCollisionBehavior::DropShadowPadding - EntityGroundCollisionBehavior::DropShadowCollisionHeight / 2.0f));

		this->addChild(dropShadowCollision);

		dropShadowCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
		{
			return CollisionResult::DoNothing;
		});

		this->dropShadowCollisions.push_back(dropShadowCollision);
	}
}

void EntityGroundCollisionBehavior::buildGroundCollisionDetector()
{
	if (this->groundCollision != nullptr)
	{
		return;
	}

	this->groundCollision = CollisionObject::create(
		CollisionObject::createBox(
			CSize(this->detectorWidth, EntityGroundCollisionBehavior::GroundCollisionHeight)
		),
		(int)PlatformerCollisionType::GroundDetector,
		CollisionObject::Properties(false, false),
		Color4F::GRAY
	);
	
	this->groundCollision->setPosition(Vec2(0.0f, EntityGroundCollisionBehavior::GroundCollisionOffset));

	this->addChild(this->groundCollision);

	this->groundCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
	{
		this->onCollideWithGround();

		return CollisionResult::DoNothing;
	});
}
