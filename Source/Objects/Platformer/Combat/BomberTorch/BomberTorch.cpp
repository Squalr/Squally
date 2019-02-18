#include "BomberTorch.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Objects/Platformer/Combat/BomberTorch/BomberTorchGenericPreview.h"

#include "Resources/EntityResources.h"
#include "Resources/ObjectResources.h"

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
	this->fire = SmartAnimationSequenceNode::create(ObjectResources::FX_TorchFire_TorchFire_0000);

	this->fire->setScale(0.15f);

	this->addChild(this->bomberTorchSprite);
	this->addChild(this->fire);
}

BomberTorch::~BomberTorch()
{
}

void BomberTorch::onEnter()
{
	super::onEnter();

	this->fire->playAnimationRepeat(ObjectResources::FX_TorchFire_TorchFire_0000, 0.005f);

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

cocos2d::Vec2 BomberTorch::getButtonOffset()
{
	return Vec2(0.0f, 64.0f);
}

HackablePreview* BomberTorch::createDefaultPreview()
{
	return BomberTorchGenericPreview::create();
}

HackablePreview* BomberTorch::createVelocityPreview()
{
	return BomberTorchGenericPreview::create();
}

HackablePreview* BomberTorch::createAccelerationPreview()
{
	return BomberTorchGenericPreview::create();
}
