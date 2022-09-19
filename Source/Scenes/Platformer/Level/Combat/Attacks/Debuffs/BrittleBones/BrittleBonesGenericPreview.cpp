#include "BrittleBonesGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

BrittleBonesGenericPreview* BrittleBonesGenericPreview::create()
{
	BrittleBonesGenericPreview* instance = new BrittleBonesGenericPreview();

	instance->autorelease();

	return instance;
}

BrittleBonesGenericPreview::BrittleBonesGenericPreview()
{
}

BrittleBonesGenericPreview::~BrittleBonesGenericPreview()
{
}

HackablePreview* BrittleBonesGenericPreview::clone()
{
	return BrittleBonesGenericPreview::create();
}

void BrittleBonesGenericPreview::onEnter()
{
	super::onEnter();
}

void BrittleBonesGenericPreview::initializePositions()
{
	super::initializePositions();
}
