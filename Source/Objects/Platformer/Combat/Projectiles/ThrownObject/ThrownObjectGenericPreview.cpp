#include "ThrownObjectGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

ThrownObjectGenericPreview* ThrownObjectGenericPreview::create(std::string objectResource)
{
	ThrownObjectGenericPreview* instance = new ThrownObjectGenericPreview(objectResource);

	instance->autorelease();

	return instance;
}

ThrownObjectGenericPreview::ThrownObjectGenericPreview(std::string objectResource)
{
	this->objectResource = objectResource;
	this->objectPreview = Sprite::create(this->objectResource);

	this->previewNode->addChild(this->objectPreview);
}

ThrownObjectGenericPreview::~ThrownObjectGenericPreview()
{
}

HackablePreview* ThrownObjectGenericPreview::clone()
{
	return ThrownObjectGenericPreview::create(this->objectResource);
}

void ThrownObjectGenericPreview::onEnter()
{
	super::onEnter();

	this->objectPreview->runAction(RepeatForever::create(RotateBy::create(1.0f, 360.0f)));
}

void ThrownObjectGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 48.0f;

	this->objectPreview->setPosition(Vec2(0.0f, 0.0f));
}
