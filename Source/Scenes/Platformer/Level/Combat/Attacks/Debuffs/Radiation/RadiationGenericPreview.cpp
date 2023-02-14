#include "RadiationGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

RadiationGenericPreview* RadiationGenericPreview::create()
{
	RadiationGenericPreview* instance = new RadiationGenericPreview();

	instance->autorelease();

	return instance;
}

RadiationGenericPreview::RadiationGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

RadiationGenericPreview::~RadiationGenericPreview()
{
}

HackablePreview* RadiationGenericPreview::clone()
{
	return RadiationGenericPreview::create();
}

void RadiationGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void RadiationGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
