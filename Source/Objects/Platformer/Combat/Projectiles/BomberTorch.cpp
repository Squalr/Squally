#include "BomberTorch.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

#define LOCAL_FUNC_TORCH_ARC 1

BomberTorch* BomberTorch::create(PlatformerAttack* associatedAttack)
{
	BomberTorch* instance = new BomberTorch(associatedAttack);

	instance->autorelease();

	return instance;
}

BomberTorch::BomberTorch(PlatformerAttack* associatedAttack) : Projectile(associatedAttack, 256.0f, 1.0f)
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
