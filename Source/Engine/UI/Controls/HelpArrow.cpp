#include "HelpArrow.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

HelpArrow* HelpArrow::create()
{
	HelpArrow* instance = new HelpArrow();

	instance->autorelease();

	return instance;
}

HelpArrow::HelpArrow()
{
	this->arrow = SmartAnimationNode::create(UIResources::HelperArrowAnimations);

	this->arrow->playAnimation();

	this->addChild(this->arrow);
}

HelpArrow::~HelpArrow()
{
}

void HelpArrow::onEnter()
{
	SmartNode::onEnter();

	this->arrow->setOpacity(0);
}

void HelpArrow::showPointer()
{
	this->arrow->runAction(FadeTo::create(0.25f, 255));
}

void HelpArrow::hidePointer()
{
	this->arrow->runAction(FadeTo::create(0.25f, 0));
}
