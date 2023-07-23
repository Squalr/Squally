#include "CauterizeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

CauterizeGenericPreview* CauterizeGenericPreview::create()
{
	CauterizeGenericPreview* instance = new CauterizeGenericPreview();

	instance->autorelease();

	return instance;
}

CauterizeGenericPreview::CauterizeGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

CauterizeGenericPreview::~CauterizeGenericPreview()
{
}

HackablePreview* CauterizeGenericPreview::clone()
{
	return CauterizeGenericPreview::create();
}

void CauterizeGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Restore_Restore_0000, 0.05f, 1.5f);
}

void CauterizeGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
