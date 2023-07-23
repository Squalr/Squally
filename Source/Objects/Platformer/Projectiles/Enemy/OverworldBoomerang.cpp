#include "OverworldBoomerang.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/EntityResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

OverworldBoomerang* OverworldBoomerang::create(PlatformerEntity* owner)
{
	OverworldBoomerang* instance = new OverworldBoomerang(owner);

	instance->autorelease();

	return instance;
}

OverworldBoomerang::OverworldBoomerang(PlatformerEntity* owner) : super(nullptr, CollisionObject::createBox(CSize(153.0f * 0.75f, 148.0f * 0.75f)), (int)PlatformerCollisionType::EnemyWeapon, false)
{
	this->owner = owner;
	this->boomerang = Sprite::create(EntityResources::Enemies_CastleValgrind_Abomination_caveman_weapon);
	this->boomerangSfx = WorldSound::create(SoundResources::Platformer_Physical_Projectiles_Woosh3);
	this->impactSfx = WorldSound::create(SoundResources::Platformer_Physical_Impact_HitSoft4);

	this->boomerang->setScale(0.6f);

	this->contentNode->addChild(this->boomerang);
	this->postFXNode->addChild(this->boomerangSfx);
	this->postFXNode->addChild(this->impactSfx);
}

OverworldBoomerang::~OverworldBoomerang()
{
}

void OverworldBoomerang::onEnter()
{
	super::onEnter();

	float velocityX = 1280.0f;
	this->boomerang->runAction(RepeatForever::create(RotateBy::create(0.5f, 360.0f)));

	if (this->owner->getAnimations()->getFlippedX())
	{
		velocityX *= -1.0f;
	}

	this->boomerang->runAction(Sequence::create(
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			this->setLaunchVelocity(Vec3(-velocityX, 0.0f, 0.0f));
		}),
		nullptr
	));
	
	this->setLaunchVelocity(Vec3(velocityX, 0.0f, 0.0f));
}

void OverworldBoomerang::runSpawnFX()
{
	super::runSpawnFX();
	
	this->boomerangSfx->play();
}

void OverworldBoomerang::runImpactFX()
{
	super::runImpactFX();

	this->impactSfx->play();
}
