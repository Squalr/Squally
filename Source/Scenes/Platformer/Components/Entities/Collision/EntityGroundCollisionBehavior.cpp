#include "EntityGroundCollisionBehavior.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EnginePhysicsTypes.h"
#include "Engine/Terrain/TerrainObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityHoverCollisionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityGroundCollisionBehavior::MapKey = "entity-ground-collisions";
const int EntityGroundCollisionBehavior::DropShadowDetectorCount = 5;
const float EntityGroundCollisionBehavior::DropShadowPadding = 32.0f;
const float EntityGroundCollisionBehavior::DropShadowCollisionHeight = 512.0f;
const float EntityGroundCollisionBehavior::GroundCollisionPadding = -4.0f;
const float EntityGroundCollisionBehavior::GroundCollisionOffset = -8.0f;
const float EntityGroundCollisionBehavior::GroundCollisionHeight = 64.0f;
const float EntityGroundCollisionBehavior::GroundCollisionRadius = 8.0f;
const float EntityGroundCollisionBehavior::CornerCollisionWidth = 32.0f;

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
	this->leftCornerCollision = nullptr;
	this->rightCornerCollision = nullptr;
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
		// this->buildCornerCollisionDetectors();
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
	
	if (this->leftCornerCollision != nullptr)
	{
		this->leftCornerCollision->setPhysicsFlagEnabled(false);
	}
	
	if (this->rightCornerCollision != nullptr)
	{
		this->rightCornerCollision->setPhysicsFlagEnabled(false);
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

	for (CollisionObject* dropShadowCollision : this->dropShadowCollisions)
	{
		if (dropShadowCollision == nullptr)
		{
			continue;
		}

		for (CollisionObject* candidateGround : dropShadowCollision->getCurrentCollisions())
		{
			DropShadowResult result = tryCastShadow(dropShadowCollision, candidateGround);

			if (result.isValid)
			{
				if (std::abs(result.slope) > M_PI / 2)
				{
					continue;
				}

				results.push_back(result);
			}
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

	if (!this->entity->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
	{
		this->deathScaler = MathUtils::clamp(this->deathScaler + dt * DeathScalerSpeed, 1.0f, MaxDeathScale);
	}
	else
	{
		this->deathScaler = MathUtils::clamp(this->deathScaler - dt * DeathScalerSpeed, 1.0f, MaxDeathScale);
	}

	float massMultiplier = MathUtils::clamp(this->entity->getEntitySize().width / 128.0f, 1.0f, 4.0f);
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
	return this->groundCollision == nullptr ? false : this->groundCollision->hasCollisions();
}

bool EntityGroundCollisionBehavior::hasLeftCornerCollision()
{
	return this->leftCornerCollision == nullptr ? false : this->leftCornerCollision->hasCollisions();
}

bool EntityGroundCollisionBehavior::hasRightCornerCollision()
{
	return this->rightCornerCollision == nullptr ? false : this->rightCornerCollision->hasCollisions();
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
		CollisionObject::createCapsulePolygon(
			CSize(this->detectorWidth, EntityGroundCollisionBehavior::GroundCollisionHeight)
		),
		(int)PlatformerCollisionType::GroundDetector,
		CollisionObject::Properties(false, false),
		Color4F::GRAY
	);
	
	this->groundCollision->setPosition(Vec2(0.0f, EntityGroundCollisionBehavior::GroundCollisionOffset));

	this->addChild(this->groundCollision);

	this->groundCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
	{
		this->onCollideWithGround();
		
		return CollisionResult::DoNothing;
	});
}

void EntityGroundCollisionBehavior::buildCornerCollisionDetectors()
{
	if (this->rightCornerCollision != nullptr || this->leftCornerCollision != nullptr)
	{
		return;
	}

	const float Buffer = 4;

	this->rightCornerCollision = CollisionObject::create(
		CollisionObject::createBox(
			CSize(EntityGroundCollisionBehavior::CornerCollisionWidth, EntityGroundCollisionBehavior::GroundCollisionHeight + Buffer)
		),
		(int)PlatformerCollisionType::GroundDetector,
		CollisionObject::Properties(false, false),
		Color4F::GRAY
	);

	this->leftCornerCollision = CollisionObject::create(
		CollisionObject::createBox(
			CSize(EntityGroundCollisionBehavior::CornerCollisionWidth, EntityGroundCollisionBehavior::GroundCollisionHeight + Buffer)
		),
		(int)PlatformerCollisionType::GroundDetector,
		CollisionObject::Properties(false, false),
		Color4F::GRAY
	);

	Vec2 offset = Vec2(this->detectorWidth / 2.0f,  EntityGroundCollisionBehavior::GroundCollisionOffset);

	this->rightCornerCollision->setPosition(offset);
	this->leftCornerCollision->setPosition(Vec2(-offset.x, offset.y));
	
	this->addChild(this->rightCornerCollision);
	this->addChild(this->leftCornerCollision);

	this->leftCornerCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
	{
		return CollisionResult::DoNothing;
	});

	this->rightCornerCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
	{
		return CollisionResult::DoNothing;
	});
}
