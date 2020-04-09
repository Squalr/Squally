#include "BlindGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

BlindGenericPreview* BlindGenericPreview::create()
{
	BlindGenericPreview* instance = new BlindGenericPreview();

	instance->autorelease();

	return instance;
}

BlindGenericPreview::BlindGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

BlindGenericPreview::~BlindGenericPreview()
{
}

HackablePreview* BlindGenericPreview::clone()
{
	return BlindGenericPreview::create();
}

void BlindGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void BlindGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
