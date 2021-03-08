#include "FloatingCrateGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

FloatingCrateGenericPreview* FloatingCrateGenericPreview::create()
{
	FloatingCrateGenericPreview* instance = new FloatingCrateGenericPreview();

	instance->autorelease();

	return instance;
}

FloatingCrateGenericPreview::FloatingCrateGenericPreview()
{
	this->previewAsteroid = Sprite::create(ObjectResources::Physics_WoodenCrate_WoodenCrate);

	this->previewAsteroid->setScale(0.35f);

	this->previewNode->addChild(this->previewAsteroid);
}

FloatingCrateGenericPreview::~FloatingCrateGenericPreview()
{
}

HackablePreview* FloatingCrateGenericPreview::clone()
{
	return FloatingCrateGenericPreview::create();
}

void FloatingCrateGenericPreview::onEnter()
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

void FloatingCrateGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 48.0f;

	this->previewAsteroid->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));
}
