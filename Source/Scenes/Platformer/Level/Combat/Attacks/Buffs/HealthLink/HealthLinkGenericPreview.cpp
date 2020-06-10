#include "HealthLinkGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

HealthLinkGenericPreview* HealthLinkGenericPreview::create()
{
	HealthLinkGenericPreview* instance = new HealthLinkGenericPreview();

	instance->autorelease();

	return instance;
}

HealthLinkGenericPreview::HealthLinkGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

HealthLinkGenericPreview::~HealthLinkGenericPreview()
{
}

HackablePreview* HealthLinkGenericPreview::clone()
{
	return HealthLinkGenericPreview::create();
}

void HealthLinkGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void HealthLinkGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
