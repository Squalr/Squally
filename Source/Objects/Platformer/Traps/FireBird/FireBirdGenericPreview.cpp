#include "FireBirdGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

FireBirdGenericPreview* FireBirdGenericPreview::create()
{
	FireBirdGenericPreview* instance = new FireBirdGenericPreview();

	instance->autorelease();

	return instance;
}

FireBirdGenericPreview::FireBirdGenericPreview()
{
	this->previewSpikes = SmartAnimationSequenceNode::create(ObjectResources::Traps_FireBird_FireBird_0000);

	this->previewSpikes->setScale(0.4f);

	this->previewNode->addChild(this->previewSpikes);
}

FireBirdGenericPreview::~FireBirdGenericPreview()
{
}

HackablePreview* FireBirdGenericPreview::clone()
{
	return FireBirdGenericPreview::create();
}

void FireBirdGenericPreview::onEnter()
{
	super::onEnter();

	this->previewSpikes->playAnimationAndReverseRepeat(ObjectResources::Traps_FireBird_FireBird_0000, 0.025f, 1.5f, 0.025f, 0.025f);
}

void FireBirdGenericPreview::initializePositions()
{
	super::initializePositions();
}
