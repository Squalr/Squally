#include "LavaFlowGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

LavaFlowGenericPreview* LavaFlowGenericPreview::create()
{
	LavaFlowGenericPreview* instance = new LavaFlowGenericPreview();

	instance->autorelease();

	return instance;
}

LavaFlowGenericPreview::LavaFlowGenericPreview()
{
	this->ripple = SmartAnimationSequenceNode::create(FXResources::FireAura_FireAura_0000);

	this->ripple->setScale(0.4f);

	this->previewNode->addChild(this->ripple);
}

LavaFlowGenericPreview::~LavaFlowGenericPreview()
{
}

HackablePreview* LavaFlowGenericPreview::clone()
{
	return LavaFlowGenericPreview::create();
}

void LavaFlowGenericPreview::onEnter()
{
	super::onEnter();

	this->ripple->playAnimationRepeat(FXResources::FireAura_FireAura_0000, 0.075f, 0.0f, true);
}

void LavaFlowGenericPreview::initializePositions()
{
	super::initializePositions();
}
