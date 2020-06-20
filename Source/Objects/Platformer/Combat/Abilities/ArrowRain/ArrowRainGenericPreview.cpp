#include "ArrowRainGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ArrowRainGenericPreview* ArrowRainGenericPreview::create(std::string arrowResource)
{
	ArrowRainGenericPreview* instance = new ArrowRainGenericPreview(arrowResource);

	instance->autorelease();

	return instance;
}

ArrowRainGenericPreview::ArrowRainGenericPreview(std::string arrowResource)
{
	this->arrowResource = arrowResource;
	this->arrow = Sprite::create(arrowResource);

	this->arrow->setRotation(180.0f);

	this->previewNode->addChild(this->arrow);
}

ArrowRainGenericPreview::~ArrowRainGenericPreview()
{
}

HackablePreview* ArrowRainGenericPreview::clone()
{
	return ArrowRainGenericPreview::create(this->arrowResource);
}

void ArrowRainGenericPreview::onEnter()
{
	super::onEnter();
}

void ArrowRainGenericPreview::initializePositions()
{
	super::initializePositions();
}
