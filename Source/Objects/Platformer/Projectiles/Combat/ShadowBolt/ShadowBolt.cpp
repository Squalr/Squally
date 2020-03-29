#include "ShadowBolt.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_FIREBALL_SPEED 11

ShadowBolt* ShadowBolt::create(PlatformerEntity* owner, PlatformerEntity* target)
{
	ShadowBolt* instance = new ShadowBolt(owner, target);

	instance->autorelease();

	return instance;
}

ShadowBolt::ShadowBolt(PlatformerEntity* owner, PlatformerEntity* target)
	: super(owner, target, true, Node::create(), Size(32.0f, 32.0f))
{
	this->shadowBoltAnim = SmartAnimationSequenceNode::create(FXResources::ShadowImpact_ShadowImpact_0000);

	this->explosionAnim = SmartAnimationSequenceNode::create();
	this->launchSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Fireball2);
	this->impactSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_FireHit1);

	this->shadowBoltAnim->playAnimationRepeat(FXResources::ShadowBolt_ShadowBolt_0000, 0.05f);

	this->postFXNode->addChild(this->launchSound);
	this->postFXNode->addChild(this->impactSound);
	this->postFXNode->addChild(this->explosionAnim);
	this->object->addChild(this->shadowBoltAnim);
}

ShadowBolt::~ShadowBolt()
{
}

void ShadowBolt::update(float dt)
{
	super::update(dt);

	if (!this->canUpdate)
	{
		return;
	}

	this->shadowBoltAnim->setFlippedX(this->getLaunchVelocity().x < 0.0f);
	
	this->setSpeedMultiplier(Vec3::ONE);
}

void ShadowBolt::runSpawnFX()
{
	this->launchSound->play();
}

void ShadowBolt::runImpactFX()
{
	this->explosionAnim->playAnimation(FXResources::ShadowImpact_ShadowImpact_0000, 0.05f, true);

	this->impactSound->play();
}
