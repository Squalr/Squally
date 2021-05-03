#include "RegenerationGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

RegenerationGenericPreview* RegenerationGenericPreview::create(std::string arrowResource)
{
	RegenerationGenericPreview* instance = new RegenerationGenericPreview(arrowResource);

	instance->autorelease();

	return instance;
}

RegenerationGenericPreview::RegenerationGenericPreview(std::string arrowResource)
{
	this->arrowResource = arrowResource;
	this->arrow = Sprite::create(arrowResource);

	this->arrow->setRotation(180.0f);

	this->previewNode->addChild(this->arrow);
}

RegenerationGenericPreview::~RegenerationGenericPreview()
{
}

HackablePreview* RegenerationGenericPreview::clone()
{
	return RegenerationGenericPreview::create(this->arrowResource);
}

void RegenerationGenericPreview::onEnter()
{
	super::onEnter();
}

void RegenerationGenericPreview::initializePositions()
{
	super::initializePositions();
}
