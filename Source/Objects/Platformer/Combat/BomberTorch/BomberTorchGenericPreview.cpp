#include "BomberTorchGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

BomberTorchGenericPreview* BomberTorchGenericPreview::create()
{
	BomberTorchGenericPreview* instance = new BomberTorchGenericPreview();

	instance->autorelease();

	return instance;
}

BomberTorchGenericPreview::BomberTorchGenericPreview()
{
	this->bomberTorch = Sprite::create(EntityResources::Enemies_EndianForest_OrcBomber_WEAPON);

	this->previewNode->addChild(this->bomberTorch);
}

BomberTorchGenericPreview::~BomberTorchGenericPreview()
{
}

HackablePreview* BomberTorchGenericPreview::clone()
{
	return BomberTorchGenericPreview::create();
}

void BomberTorchGenericPreview::onEnter()
{
	super::onEnter();

	this->bomberTorch->runAction(RepeatForever::create(RotateBy::create(1.0f, 360.0f)));
}

void BomberTorchGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 48.0f;

	this->bomberTorch->setPosition(Vec2(0.0f, 0.0f));
}
