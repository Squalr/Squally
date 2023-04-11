#include "FireRainGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

FireRainGenericPreview* FireRainGenericPreview::create()
{
	FireRainGenericPreview* instance = new FireRainGenericPreview();

	instance->autorelease();

	return instance;
}

FireRainGenericPreview::FireRainGenericPreview()
{
	this->fireRain = SmartAnimationSequenceNode::create(FXResources::FireBomb_FireBomb_0000);

	this->fireRain->setScale(0.25f);

	this->previewNode->addChild(this->fireRain);
}

FireRainGenericPreview::~FireRainGenericPreview()
{
}

HackablePreview* FireRainGenericPreview::clone()
{
	return FireRainGenericPreview::create();
}

void FireRainGenericPreview::onEnter()
{
	super::onEnter();

	this->fireRain->playAnimationRepeat(FXResources::FireBomb_FireBomb_0000, 0.05f);
}

void FireRainGenericPreview::initializePositions()
{
	super::initializePositions();
}
