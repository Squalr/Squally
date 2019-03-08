#include "FloatingWoodenBeamGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

FloatingWoodenBeamGenericPreview* FloatingWoodenBeamGenericPreview::create()
{
	FloatingWoodenBeamGenericPreview* instance = new FloatingWoodenBeamGenericPreview();

	instance->autorelease();

	return instance;
}

FloatingWoodenBeamGenericPreview::FloatingWoodenBeamGenericPreview()
{
	this->previewAsteroid = Sprite::create(ObjectResources::Physics_WoodenBeam_WoodenBeam);

	this->previewAsteroid->setScale(0.35f);

	this->previewNode->addChild(this->previewAsteroid);
}

HackablePreview* FloatingWoodenBeamGenericPreview::clone()
{
	return FloatingWoodenBeamGenericPreview::create();
}

void FloatingWoodenBeamGenericPreview::onEnter()
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

void FloatingWoodenBeamGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 48.0f;

	this->previewAsteroid->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));
}
