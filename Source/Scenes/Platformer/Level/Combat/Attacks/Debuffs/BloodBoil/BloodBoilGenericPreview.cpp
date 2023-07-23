#include "BloodBoilGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

BloodBoilGenericPreview* BloodBoilGenericPreview::create()
{
	BloodBoilGenericPreview* instance = new BloodBoilGenericPreview();

	instance->autorelease();

	return instance;
}

BloodBoilGenericPreview::BloodBoilGenericPreview()
{
}

BloodBoilGenericPreview::~BloodBoilGenericPreview()
{
}

HackablePreview* BloodBoilGenericPreview::clone()
{
	return BloodBoilGenericPreview::create();
}

void BloodBoilGenericPreview::onEnter()
{
	super::onEnter();
}

void BloodBoilGenericPreview::initializePositions()
{
	super::initializePositions();
}
