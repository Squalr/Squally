#include "OverworldArrow.h"

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

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

OverworldArrow* OverworldArrow::create(PlatformerEntity* owner, const std::string& spriteResource)
{
	OverworldArrow* instance = new OverworldArrow(owner, spriteResource);

	instance->autorelease();

	return instance;
}

OverworldArrow::OverworldArrow(PlatformerEntity* owner, const std::string& spriteResource) : super(nullptr, CollisionObject::createBox(CSize(139.0f, 20.0f)), (int)PlatformerCollisionType::EnemyWeapon, false)
{
	this->owner = owner;
	this->arrow = Sprite::create(spriteResource);
	this->arrowSfx = WorldSound::create(SoundResources::Platformer_Physical_Projectiles_WeaponThrow3);
	this->impactSfx = WorldSound::create(SoundResources::Platformer_Physical_Impact_HitSoft1);

	this->contentNode->addChild(this->arrow);
	this->postFXNode->addChild(this->arrowSfx);
	this->postFXNode->addChild(this->impactSfx);
}

OverworldArrow::~OverworldArrow()
{
}

void OverworldArrow::onEnter()
{
	super::onEnter();

	float velocityX = 2048.0f;
	this->arrow->setRotation(90.0f);

	if (this->owner->getAnimations()->getFlippedX())
	{
		velocityX *= -1.0f;
		this->arrow->setRotation(-90.0f);
	}
	
	this->setLaunchVelocity(Vec3(velocityX, 0.0f, 0.0f));
}

void OverworldArrow::runSpawnFX()
{
	super::runSpawnFX();
	
	this->arrowSfx->play();
}

void OverworldArrow::runImpactFX()
{
	super::runImpactFX();

	this->impactSfx->play();
}
