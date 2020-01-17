#include "FireballGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

FireballGenericPreview* FireballGenericPreview::create()
{
	FireballGenericPreview* instance = new FireballGenericPreview();

	instance->autorelease();

	return instance;
}

FireballGenericPreview::FireballGenericPreview()
{
	this->fireball = SmartAnimationSequenceNode::create(FXResources::FireBall_FireBall_0000);

	this->previewNode->addChild(this->fireball);
}

FireballGenericPreview::~FireballGenericPreview()
{
}

HackablePreview* FireballGenericPreview::clone()
{
	return FireballGenericPreview::create();
}

void FireballGenericPreview::onEnter()
{
	super::onEnter();

	this->fireball->playAnimationRepeat(FXResources::FireBall_FireBall_0000, 0.085f);
}

void FireballGenericPreview::initializePositions()
{
	super::initializePositions();
}
