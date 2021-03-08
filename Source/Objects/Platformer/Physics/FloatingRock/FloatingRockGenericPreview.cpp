#include "FloatingRockGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

FloatingRockGenericPreview* FloatingRockGenericPreview::create()
{
	FloatingRockGenericPreview* instance = new FloatingRockGenericPreview();

	instance->autorelease();

	return instance;
}

FloatingRockGenericPreview::FloatingRockGenericPreview()
{
	this->previewAsteroid = Sprite::create(ObjectResources::Physics_RollingStone_RollingStone);

	this->previewAsteroid->setScale(0.35f);

	this->previewNode->addChild(this->previewAsteroid);
}

FloatingRockGenericPreview::~FloatingRockGenericPreview()
{
}

HackablePreview* FloatingRockGenericPreview::clone()
{
	return FloatingRockGenericPreview::create();
}

void FloatingRockGenericPreview::onEnter()
{
	super::onEnter();

	const float offset = 48.0f;

	this->previewAsteroid->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, -(HackablePreview::PreviewRadius - offset)))),
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, HackablePreview::PreviewRadius - offset))),
			nullptr
		))
	);
}

void FloatingRockGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 48.0f;

	this->previewAsteroid->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));
}
