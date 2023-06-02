#include "OverworldArrow.h"

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

OverworldArrow* OverworldArrow::create(const std::string& spriteResource)
{
	OverworldArrow* instance = new OverworldArrow(spriteResource);

	instance->autorelease();

	return instance;
}

OverworldArrow::OverworldArrow(const std::string& spriteResource) : super(nullptr, CollisionObject::createCapsulePolygon(CSize(48.0f, 48.0f)), (int)PlatformerCollisionType::EnemyWeapon, false)
{
	this->arrow = Sprite::create(spriteResource);
	this->arrowSfx = WorldSound::create(SoundResources::Platformer_Physical_Projectiles_WeaponThrow3);
	this->impactSfx = WorldSound::create(SoundResources::Platformer_Physical_Impact_HitSoft1);

	this->arrow->setRotation(90.0f);

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

	this->setLaunchVelocity(Vec3(2048.0f, 0.0f, 0.0f));
}

void OverworldArrow::runSpawnFX()
{
	super::runSpawnFX();
	
	this->arrowSfx->play();
}

void OverworldArrow::runImpactFX()
{
	super::runImpactFX();

	this->setLaunchVelocity(Vec3::ZERO);
	
	this->impactSfx->play();
}
