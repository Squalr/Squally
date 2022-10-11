#include "RegenerationGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

RegenerationGenericPreview* RegenerationGenericPreview::create()
{
	RegenerationGenericPreview* instance = new RegenerationGenericPreview();

	instance->autorelease();

	return instance;
}

RegenerationGenericPreview::RegenerationGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

RegenerationGenericPreview::~RegenerationGenericPreview()
{
}

HackablePreview* RegenerationGenericPreview::clone()
{
	return RegenerationGenericPreview::create();
}

void RegenerationGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Restore_Restore_0000, 0.05f, 1.5f);
}

void RegenerationGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
