#include "Waterball.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"
#include "Resources/FXResources.h"

using namespace cocos2d;

Waterball* Waterball::create(float waterballRotation, float waterballSpeed)
{
	Waterball* instance = new Waterball(waterballRotation, waterballSpeed);

	instance->autorelease();

	return instance;
}

Waterball::Waterball(float waterballRotation, float waterballSpeed) : super(nullptr, CollisionObject::createBox(CSize(128.0f, 128.0f)), (int)PlatformerCollisionType::Water, false)
{
	this->waterballSpeed = waterballSpeed;
	this->waterballAnim = SmartAnimationSequenceNode::create();

	this->setProjectileRotation(waterballRotation);
	this->setLaunchVelocity(Vec3(this->waterballSpeed * std::cos(waterballRotation), this->waterballSpeed * std::sin(waterballRotation), 0.0f));

	this->setMovementMode(Projectile::MovementMode::RotationVelocity);

	this->contentNode->addChild(this->waterballAnim);
}

Waterball::~Waterball()
{
}

void Waterball::onEnter()
{
	super::onEnter();
	
	this->waterballAnim->setVisible(false);
}

void Waterball::runSpawnFX()
{
	super::runSpawnFX();

	this->waterballAnim->playAnimationRepeat(FXResources::WaterBall_WaterBall_0000, 0.05f);
	this->waterballAnim->setVisible(true);
}

void Waterball::runImpactFX()
{
	super::runImpactFX();

	this->waterballAnim->setVisible(false);
}
