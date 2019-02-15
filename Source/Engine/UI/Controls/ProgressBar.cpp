#include "ProgressBar.h"

#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Utils/MathUtils.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

ProgressBar* ProgressBar::create(std::string frameResource, std::string fillResource, cocos2d::Vec2 fillOffset, bool isHorizontal)
{
	return ProgressBar::create(Sprite::create(frameResource), Sprite::create(fillResource), fillOffset, isHorizontal);
}

ProgressBar* ProgressBar::create(Node* frame, Node* fill, Vec2 fillOffset, bool isHorizontal)
{
	ProgressBar* instance = new ProgressBar(frame, fill, fillOffset, isHorizontal);

	instance->autorelease();

	return instance;
}

ProgressBar::ProgressBar(Node* frame, Node* fill, Vec2 fillOffset, bool isHorizontal)
{
	this->isHorizontal = isHorizontal;
	this->frame = frame;
	this->progressBar = fill;
	this->progressClip = ClippingRectangleNode::create(Rect(-Vec2(this->progressBar->getContentSize() / 2.0f), this->progressBar->getContentSize()));
	
	this->progressClip->setPosition(Vec2(fillOffset.x, fillOffset.y));
	this->setProgress(0.0f);

	this->setContentSize(this->frame->getContentSize());

	this->progressClip->addChild(this->progressBar);
	this->addChild(this->frame);
	this->addChild(this->progressClip);
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::initializePositions()
{
	super::initializePositions();
}

void ProgressBar::setProgress(float newProgress)
{
	this->progress = MathUtils::clamp(newProgress, 0.0f, 1.0f);

	// Update progress bar
	Rect newClippingRegion = this->progressClip->getClippingRegion();

	if (this->isHorizontal)
	{
		newClippingRegion.size = Size(this->progressBar->getContentSize().width * this->progress, this->progressBar->getContentSize().height);
	}
	else
	{
		newClippingRegion.size = Size(this->progressBar->getContentSize().width, this->progressBar->getContentSize().height * this->progress);
	}
	
	this->progressClip->setClippingRegion(newClippingRegion);
}
