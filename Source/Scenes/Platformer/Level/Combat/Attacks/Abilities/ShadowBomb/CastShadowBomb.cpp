#include "CastShadowBomb.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Combat/Abilities/ShadowBomb/ShadowBomb.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastShadowBomb* CastShadowBomb::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastShadowBomb* instance = new CastShadowBomb(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastShadowBomb::CastShadowBomb(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Damage, UIResources::Menus_Icons_SpellImpactPurple, priority, AbilityType::Shadow, 0, 0, 4, attackDuration, recoverDuration, TargetingType::Single)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastShadowBomb::~CastShadowBomb()
{
}

void CastShadowBomb::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastShadowBomb::cloneInternal()
{
	return CastShadowBomb::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastShadowBomb::getString()
{
	return Strings::Menus_Hacking_Abilities_Abilities_ShadowBomb_ShadowBomb::create();
}

std::string CastShadowBomb::getAttackAnimation()
{
	return "AttackCast";
}

void CastShadowBomb::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	if (targets.size() <= 0)
	{
		return;
	}

	PlatformerEntity* target = targets[0];

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	ShadowBomb* shadowBomb = ShadowBomb::create(owner, nullptr);

	ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
		target,
		shadowBomb,
		SpawnMethod::Above,
		PositionMode::Discard,
		[&]()
		{
		},
		[&]()
		{
		}
	));

	GameUtils::setWorldCoords3D(shadowBomb, GameUtils::getWorldCoords3D(target, false) + Vec3(0.0f, 64.0f, 0.0f));
}

void CastShadowBomb::onCleanup()
{
}
