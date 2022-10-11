#include "PendulumBladeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

PendulumBladeGenericPreview* PendulumBladeGenericPreview::create()
{
	PendulumBladeGenericPreview* instance = new PendulumBladeGenericPreview();

	instance->autorelease();

	return instance;
}

PendulumBladeGenericPreview::PendulumBladeGenericPreview()
{
	this->previewBlade = Sprite::create(ObjectResources::Traps_PendulumBlade_PreviewBlade);

	this->previewBlade->setAnchorPoint(Vec2(0.5f, 1.0f));

	this->previewNode->addChild(this->previewBlade);
}

PendulumBladeGenericPreview::~PendulumBladeGenericPreview()
{
}

HackablePreview* PendulumBladeGenericPreview::clone()
{
	return PendulumBladeGenericPreview::create();
}

void PendulumBladeGenericPreview::onEnter()
{
	super::onEnter();

	this->previewBlade->setRotation(45.0f);

	this->previewBlade->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(RotateTo::create(1.5f, 315.0f)),
			EaseSineInOut::create(RotateTo::create(1.5f, 45.0f)),
			nullptr
		))
	);
}

void PendulumBladeGenericPreview::initializePositions()
{
	super::initializePositions();
}
