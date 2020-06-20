#include "EnergyBolt.h"

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

EnergyBolt* EnergyBolt::create()
{
	EnergyBolt* instance = new EnergyBolt();

	instance->autorelease();

	return instance;
}

EnergyBolt::EnergyBolt() : super(nullptr, CollisionObject::createCapsulePolygon(Size(48.0f, 48.0f)), (int)PlatformerCollisionType::PlayerWeapon, false)
{
	this->energyBolt = SmartAnimationSequenceNode::create(FXResources::ElectricOrb_ElectricOrb_0000);
	this->energySfx = WorldSound::create(SoundResources::Platformer_Spells_ElectricZap1);

	this->contentNode->addChild(this->energyBolt);
	this->postFXNode->addChild(this->energySfx);
}

EnergyBolt::~EnergyBolt()
{
}

void EnergyBolt::onEnter()
{
	super::onEnter();

	this->setLaunchVelocity(Vec3(2048.0f, 0.0f, 0.0f));

	this->energyBolt->playAnimationRepeat(FXResources::ElectricOrb_ElectricOrb_0000, 0.05f);
}

void EnergyBolt::runSpawnFX()
{
	super::runSpawnFX();

	this->energySfx->play();
}
