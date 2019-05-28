#include "RestoreHealthGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

RestoreHealthGenericPreview* RestoreHealthGenericPreview::create()
{
	RestoreHealthGenericPreview* instance = new RestoreHealthGenericPreview();

	instance->autorelease();

	return instance;
}

RestoreHealthGenericPreview::RestoreHealthGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

RestoreHealthGenericPreview::~RestoreHealthGenericPreview()
{
}

HackablePreview* RestoreHealthGenericPreview::clone()
{
	return RestoreHealthGenericPreview::create();
}

void RestoreHealthGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void RestoreHealthGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
