#include "BatSwarmGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

BatSwarmGenericPreview* BatSwarmGenericPreview::create(std::string arrowResource)
{
	BatSwarmGenericPreview* instance = new BatSwarmGenericPreview(arrowResource);

	instance->autorelease();

	return instance;
}

BatSwarmGenericPreview::BatSwarmGenericPreview(std::string arrowResource)
{
	this->arrowResource = arrowResource;
	this->arrow = Sprite::create(arrowResource);

	this->arrow->setRotation(180.0f);

	this->previewNode->addChild(this->arrow);
}

BatSwarmGenericPreview::~BatSwarmGenericPreview()
{
}

HackablePreview* BatSwarmGenericPreview::clone()
{
	return BatSwarmGenericPreview::create(this->arrowResource);
}

void BatSwarmGenericPreview::onEnter()
{
	super::onEnter();
}

void BatSwarmGenericPreview::initializePositions()
{
	super::initializePositions();
}
