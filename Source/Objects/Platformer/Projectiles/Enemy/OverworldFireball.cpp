#include "OverworldFireball.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

OverworldFireball* OverworldFireball::create()
{
	OverworldFireball* instance = new OverworldFireball();

	instance->autorelease();

	return instance;
}

OverworldFireball::OverworldFireball() : super(nullptr, CollisionObject::createCapsulePolygon(Size(48.0f, 48.0f)), (int)PlatformerCollisionType::EnemyWeapon, false)
{
	this->fireball = SmartAnimationSequenceNode::create();
	this->explosion = SmartAnimationSequenceNode::create();
	this->fireballSfx = WorldSound::create(SoundResources::Platformer_Spells_Fireball2);
	this->impactSfx = WorldSound::create(SoundResources::Platformer_Spells_FireHit1);

	this->contentNode->addChild(this->fireball);
	this->contentNode->addChild(this->explosion);
	this->postFXNode->addChild(this->fireballSfx);
	this->postFXNode->addChild(this->impactSfx);
}

OverworldFireball::~OverworldFireball()
{
}

void OverworldFireball::onEnter()
{
	super::onEnter();

	this->setLaunchVelocity(Vec3(2048.0f, 0.0f, 0.0f));
}

void OverworldFireball::runSpawnFX()
{
	super::runSpawnFX();
	
	this->fireball->playAnimationRepeat(FXResources::FireBall_FireBall_0000, 0.05f);
	this->fireballSfx->play();
}

void OverworldFireball::runImpactFX()
{
	super::runImpactFX();

	this->setLaunchVelocity(Vec3::ZERO);
	
	this->fireball->stopAnimation();
	this->explosion->playAnimation(FXResources::Explosion_Explosion_0000, 0.05f, true);
	this->impactSfx->play();
}
