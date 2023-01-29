#include "Acid.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/Liquid/LiquidNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Decor/AcidFX.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Acid::MapKey = "acid";
const Color4B Acid::SurfaceColor = Color4B(143, 231, 84, 255);
const Color4B Acid::BodyColor = Color4B(64, 224, 32, 240);
const float Acid::AcidGravity = 0.0f;
const float Acid::BubbleDensityPer1024Px = 1.0f;

Acid* Acid::create(ValueMap& properties)
{
	Acid* instance = new Acid(properties);

	instance->autorelease();

	return instance;
}

Acid::Acid(ValueMap& properties) : super(properties, 8.0f, (CollisionType)PlatformerCollisionType::KillPlane, Acid::SurfaceColor, Acid::BodyColor, 0.025f, 0.015f, 0.15f)
{
	int bubbleInstances = int(this->liquidSize.width * Acid::BubbleDensityPer1024Px / 1024.0f);
	ValueMap bubbleProperties;

	for (int index = 0; index < bubbleInstances; index++)
	{
		AcidFX* instance = AcidFX::create(bubbleProperties);
		instance->setPositionY(this->liquidSize.height / 2.0f);
		this->bubbles.push_back(instance);
		this->addChild(instance);
	}
}

Acid::~Acid()
{
}

void Acid::onEnter()
{
	super::onEnter();

	this->runBubbles();
}

void Acid::initializeListeners()
{
	super::initializeListeners();

	this->liquidCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
	{
		this->runObjectSplash(collisionData.other, false);

		return CollisionResult::DoNothing;
	});

	this->liquidCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
	{
		this->runObjectSplash(collisionData.other, true);

		return CollisionResult::DoNothing;
	});

	this->liquidCollision->whileCollidesWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
	{
		this->applyAcidForce(collisionData.other, collisionData.dt);

		return CollisionResult::DoNothing;
	});
}

void Acid::applyAcidForce(CollisionObject* target, float dt)
{
	target->setVelocity(target->getVelocity() + Vec2(0.0f, Acid::AcidGravity * dt));
}

void Acid::runBubbles()
{
	for (int index = 0; index < int(this->bubbles.size()); index++)
	{
		this->runAction(Sequence::create(
			DelayTime::create(RandomHelper::random_real(0.0f, 8.0f)),
			CallFunc::create([=]()
			{
				this->runBubble(index);
				this->runBubbleLoop(index);
			}),
			nullptr
		));
	}
}

void Acid::runBubbleLoop(int index)
{
    if (this->bubblesDisabled)
    {
        return;
    }

	this->runAction(Sequence::create(
		DelayTime::create(RandomHelper::random_real(8.0f, 16.0f)),
		CallFunc::create([=]()
		{
			this->runBubble(index);
			this->runBubbleLoop(index);
		}),
		nullptr
	));
}

void Acid::runBubble(int index)
{
	float bucketStart = float(index) / float(this->bubbles.size()) * this->liquidSize.width;
	float bucketSize = this->liquidSize.width / float(this->bubbles.size());
	float x = bucketStart + RandomHelper::random_real(std::min(64.0f, bucketSize), bucketSize) - this->liquidSize.width / 2.0f;

	this->bubbles[index]->setScale(RandomHelper::random_real(0.25f, 1.0f));
	this->bubbles[index]->setPositionX(x);
	this->bubbles[index]->runAnimation();
}
