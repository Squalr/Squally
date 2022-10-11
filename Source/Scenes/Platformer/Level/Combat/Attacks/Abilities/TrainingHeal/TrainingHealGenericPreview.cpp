#include "TrainingHealGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

TrainingHealGenericPreview* TrainingHealGenericPreview::create()
{
	TrainingHealGenericPreview* instance = new TrainingHealGenericPreview();

	instance->autorelease();

	return instance;
}

TrainingHealGenericPreview::TrainingHealGenericPreview()
{
	this->healEffect = SmartAnimationSequenceNode::create();

	this->previewNode->addChild(this->healEffect);
}

TrainingHealGenericPreview::~TrainingHealGenericPreview()
{
}

HackablePreview* TrainingHealGenericPreview::clone()
{
	return TrainingHealGenericPreview::create();
}

void TrainingHealGenericPreview::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f, 1.5f);
}

void TrainingHealGenericPreview::initializePositions()
{
	super::initializePositions();

	this->healEffect->setPosition(Vec2(0.0f, 0.0f));
}
