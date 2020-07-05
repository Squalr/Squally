#include "ReflectGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ReflectGenericPreview* ReflectGenericPreview::create()
{
	ReflectGenericPreview* instance = new ReflectGenericPreview();

	instance->autorelease();

	return instance;
}

ReflectGenericPreview::ReflectGenericPreview()
{
}

ReflectGenericPreview::~ReflectGenericPreview()
{
}

HackablePreview* ReflectGenericPreview::clone()
{
	return ReflectGenericPreview::create();
}

void ReflectGenericPreview::onEnter()
{
	super::onEnter();
}

void ReflectGenericPreview::initializePositions()
{
	super::initializePositions();
}
