#include "ArrowVolleyGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ArrowVolleyGenericPreview* ArrowVolleyGenericPreview::create(std::string arrowResource)
{
	ArrowVolleyGenericPreview* instance = new ArrowVolleyGenericPreview(arrowResource);

	instance->autorelease();

	return instance;
}

ArrowVolleyGenericPreview::ArrowVolleyGenericPreview(std::string arrowResource)
{
	this->arrowResource = arrowResource;
	this->arrow = Sprite::create(arrowResource);

	this->arrow->setRotation(180.0f);

	this->previewNode->addChild(this->arrow);
}

ArrowVolleyGenericPreview::~ArrowVolleyGenericPreview()
{
}

HackablePreview* ArrowVolleyGenericPreview::clone()
{
	return ArrowVolleyGenericPreview::create(this->arrowResource);
}

void ArrowVolleyGenericPreview::onEnter()
{
	super::onEnter();
}

void ArrowVolleyGenericPreview::initializePositions()
{
	super::initializePositions();
}
