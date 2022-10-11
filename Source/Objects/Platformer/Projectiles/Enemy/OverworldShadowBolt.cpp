#include "OverworldShadowBolt.h"

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
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

OverworldShadowBolt* OverworldShadowBolt::create()
{
	OverworldShadowBolt* instance = new OverworldShadowBolt();

	instance->autorelease();

	return instance;
}

OverworldShadowBolt::OverworldShadowBolt() : super(nullptr, CollisionObject::createCapsulePolygon(CSize(48.0f, 48.0f)), (int)PlatformerCollisionType::EnemyWeapon, false)
{
	this->shadowBolt = SmartAnimationSequenceNode::create();
	this->explosion = SmartAnimationSequenceNode::create();
	this->shadowBoltSfx = WorldSound::create(SoundResources::Platformer_Spells_Fireball2);
	this->impactSfx = WorldSound::create(SoundResources::Platformer_Spells_FireHit1);

	this->shadowBolt->setFlippedX(true);

	this->contentNode->addChild(this->shadowBolt);
	this->contentNode->addChild(this->explosion);
	this->postFXNode->addChild(this->shadowBoltSfx);
	this->postFXNode->addChild(this->impactSfx);
}

OverworldShadowBolt::~OverworldShadowBolt()
{
}

void OverworldShadowBolt::onEnter()
{
	super::onEnter();

	this->setLaunchVelocity(Vec3(2048.0f, 0.0f, 0.0f));
}

void OverworldShadowBolt::runSpawnFX()
{
	super::runSpawnFX();
	
	this->shadowBolt->playAnimationRepeat(FXResources::ShadowBolt_ShadowBolt_0000, 0.05f);
	this->shadowBoltSfx->play();
}

void OverworldShadowBolt::runImpactFX()
{
	super::runImpactFX();

	this->setLaunchVelocity(Vec3::ZERO);
	
	this->shadowBolt->stopAnimation();
	this->explosion->playAnimation(FXResources::Explosion_Explosion_0000, 0.05f, true);
	this->impactSfx->play();
}
