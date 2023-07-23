#include "Shell.h"

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

#include "Resources/ObjectResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

Shell* Shell::create()
{
	Shell* instance = new Shell();

	instance->autorelease();

	return instance;
}

Shell::Shell() : super(nullptr, CollisionObject::createCapsulePolygon(CSize(48.0f, 48.0f)), (int)PlatformerCollisionType::PlayerWeapon, false)
{
	this->shell = Sprite::create(ObjectResources::Interactive_GatlingGun_Bullet);
	this->shootSfx = WorldSound::create(SoundResources::Platformer_FX_Explosions_ExplosionSoftReverb1);
	this->hitSfx = WorldSound::create(SoundResources::Platformer_FX_Explosions_ExplosionSoft1);
	this->critSfx = WorldSound::create(SoundResources::Platformer_FX_Explosions_Explosion1);
	this->damageFx = SmartAnimationSequenceNode::create();

	this->contentNode->addChild(this->shell);
	this->postFXNode->addChild(this->shootSfx);
	this->postFXNode->addChild(this->hitSfx);
	this->postFXNode->addChild(this->critSfx);
	this->postFXNode->addChild(this->damageFx);
}

Shell::~Shell()
{
}

void Shell::onEnter()
{
	super::onEnter();
}

void Shell::runSpawnFX()
{
	super::runSpawnFX();

	this->shootSfx->play();
	this->shell->setVisible(true);
	this->setLaunchVelocity(Vec3(2048.0f, 0.0f, 0.0f));
}

void Shell::runImpactFX(bool isCrit)
{
	this->shell->setVisible(false);
	this->setLaunchVelocity(Vec3::ZERO);

	if (isCrit)
	{
		this->critSfx->play();
		this->damageFx->playAnimation(FXResources::ExplosionNormal_Explosion_0000, 0.035f, true);
	}
	else
	{
		this->hitSfx->play();
		this->damageFx->playAnimation(FXResources::FireBurst_FireBurst_0000, 0.035f, true);
	}
}
