#include "CProgressBar.h"

#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Utils/MathUtils.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

CProgressBar* CProgressBar::create(Sprite* frame, Sprite* fill, Vec2 fillOffset)
{
	CProgressBar* instance = new CProgressBar(frame, fill, fillOffset);

	instance->autorelease();

	return instance;
}

CProgressBar::CProgressBar(Sprite* frame, Sprite* fill, Vec2 fillOffset)
{
	this->frame = frame;
	this->progressBar = fill;
	this->progressClip = ClippingRectangleNode::create(Rect(-this->progressBar->getContentSize().width / 2.0f, -this->progressBar->getContentSize().height / 2.0f, this->progressBar->getContentSize().width, this->progressBar->getContentSize().height));

	this->progressClip->setPosition(Vec2(fillOffset.x, fillOffset.y));
	this->setProgress(0.0f);

	this->setContentSize(this->frame->getContentSize());

	this->progressClip->addChild(this->progressBar);
	this->addChild(this->frame);
	this->addChild(this->progressClip);
}

CProgressBar::~CProgressBar()
{
}

void CProgressBar::initializePositions()
{
	super::initializePositions();
}

void CProgressBar::setProgress(float newProgress)
{
	this->progress = MathUtils::clamp(newProgress, 0.0f, 1.0f);

	// Update progress bar
	Rect newClippingRegion = this->progressClip->getClippingRegion();
	newClippingRegion.size = Size(this->progressBar->getContentSize().width * this->progress, newClippingRegion.size.height);
	this->progressClip->setClippingRegion(newClippingRegion);
}
