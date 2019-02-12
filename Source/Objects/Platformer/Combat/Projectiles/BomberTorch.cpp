#include "BomberTorch.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionType.h"

#include "Resources/EntityResources.h"

#include "Strings/Hacking/Objects/PendulumBlade/SetTargetAngle/SetTargetAngle.h"

using namespace cocos2d;

#define LOCAL_FUNC_TORCH_ARC 1

BomberTorch* BomberTorch::create()
{
	BomberTorch* instance = new BomberTorch();

	instance->autorelease();

	return instance;
}

BomberTorch::BomberTorch() : ProximityObject(32.0f)
{
	this->bomberTorchSprite = Sprite::create(EntityResources::Enemies_EndianForest_OrcBomber_WEAPON);

	this->addChild(this->bomberTorchSprite);
}

BomberTorch::~BomberTorch()
{
}

void BomberTorch::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void BomberTorch::initializePositions()
{
	super::initializePositions();
}

void BomberTorch::update(float dt)
{
	super::update(dt);
}
