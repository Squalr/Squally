#include "CurseOfTonguesGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

CurseOfTonguesGenericPreview* CurseOfTonguesGenericPreview::create()
{
	CurseOfTonguesGenericPreview* instance = new CurseOfTonguesGenericPreview();

	instance->autorelease();

	return instance;
}

CurseOfTonguesGenericPreview::CurseOfTonguesGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

CurseOfTonguesGenericPreview::~CurseOfTonguesGenericPreview()
{
}

HackablePreview* CurseOfTonguesGenericPreview::clone()
{
	return CurseOfTonguesGenericPreview::create();
}

void CurseOfTonguesGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void CurseOfTonguesGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
