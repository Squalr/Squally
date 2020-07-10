#include "StalactiteGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

StalactiteGenericPreview* StalactiteGenericPreview::create()
{
	StalactiteGenericPreview* instance = new StalactiteGenericPreview();

	instance->autorelease();

	return instance;
}

StalactiteGenericPreview::StalactiteGenericPreview()
{
	this->previewStalactite = Sprite::create(ObjectResources::Traps_Stalactite_Stalactite);

	this->previewStalactite->setAnchorPoint(Vec2(0.5f, 1.0f));

	this->previewNode->addChild(this->previewStalactite);
}

HackablePreview* StalactiteGenericPreview::clone()
{
	return StalactiteGenericPreview::create();
}

void StalactiteGenericPreview::onEnter()
{
	super::onEnter();

	const float offset = 48.0f;

	this->previewStalactite->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, -(HackablePreview::PreviewRadius - offset)))),
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, HackablePreview::PreviewRadius - offset))),
			nullptr
		))
	);
}

void StalactiteGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 48.0f;

	this->previewStalactite->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));
}
