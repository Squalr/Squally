#include "AddHealthGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

AddHealthGenericPreview* AddHealthGenericPreview::create()
{
	AddHealthGenericPreview* instance = new AddHealthGenericPreview();

	instance->autorelease();

	return instance;
}

AddHealthGenericPreview::AddHealthGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

AddHealthGenericPreview::~AddHealthGenericPreview()
{
}

HackablePreview* AddHealthGenericPreview::clone()
{
	return AddHealthGenericPreview::create();
}

void AddHealthGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void AddHealthGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
