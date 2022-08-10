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
	this->shell = SmartAnimationSequenceNode::create(FXResources::ElectricOrb_ElectricOrb_0000);
	this->shootSfx = WorldSound::create(SoundResources::Platformer_Spells_ElectricZap1);

	this->contentNode->addChild(this->shell);
	this->postFXNode->addChild(this->shootSfx);
}

Shell::~Shell()
{
}

void Shell::onEnter()
{
	super::onEnter();

	this->setLaunchVelocity(Vec3(2048.0f, 0.0f, 0.0f));

	this->shell->playAnimationRepeat(FXResources::ElectricOrb_ElectricOrb_0000, 0.05f);
}

void Shell::runSpawnFX()
{
	super::runSpawnFX();

	this->shootSfx->play();
}
