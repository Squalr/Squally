#include "WaterballGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

WaterballGenericPreview* WaterballGenericPreview::create()
{
	WaterballGenericPreview* instance = new WaterballGenericPreview();

	instance->autorelease();

	return instance;
}

WaterballGenericPreview::WaterballGenericPreview()
{
	this->waterball = SmartAnimationSequenceNode::create(FXResources::FireBall_FireBall_0000);

	this->previewNode->addChild(this->waterball);
}

WaterballGenericPreview::~WaterballGenericPreview()
{
}

HackablePreview* WaterballGenericPreview::clone()
{
	return WaterballGenericPreview::create();
}

void WaterballGenericPreview::onEnter()
{
	super::onEnter();

	this->waterball->playAnimationRepeat(FXResources::FireBall_FireBall_0000, 0.085f);
}

void WaterballGenericPreview::initializePositions()
{
	super::initializePositions();
}
