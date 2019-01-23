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
	this->progressClip = ClippingRectangleNode::create(Rect(0, -this->progressBar->getContentSize().height / 2.0f, this->progressBar->getContentSize().width, this->progressBar->getContentSize().height));

	this->frame->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->progressBar->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->progressClip->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->progressClip->setPosition(Vec2(fillOffset.x, fillOffset.y - this->frame->getContentSize().height / 2.0f));
	this->setProgress(0.0f);

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
