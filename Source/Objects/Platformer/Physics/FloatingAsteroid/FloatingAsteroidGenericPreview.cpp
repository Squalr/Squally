#include "FloatingAsteroidGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

FloatingAsteroidGenericPreview* FloatingAsteroidGenericPreview::create()
{
	FloatingAsteroidGenericPreview* instance = new FloatingAsteroidGenericPreview();

	instance->autorelease();

	return instance;
}

FloatingAsteroidGenericPreview::FloatingAsteroidGenericPreview()
{
	this->previewAsteroid = Sprite::create(ObjectResources::Physics_Asteroid_Asteroid);

	this->previewAsteroid->setScale(0.35f);

	this->previewNode->addChild(this->previewAsteroid);
}

HackablePreview* FloatingAsteroidGenericPreview::clone()
{
	return FloatingAsteroidGenericPreview::create();
}

void FloatingAsteroidGenericPreview::onEnter()
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

void FloatingAsteroidGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 48.0f;

	this->previewAsteroid->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));
}
