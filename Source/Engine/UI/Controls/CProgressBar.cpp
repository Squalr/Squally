#include "CProgressBar.h"

#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

CProgressBar* CProgressBar::create()
{
	CProgressBar* instance = new CProgressBar();

	instance->autorelease();

	return instance;
}

CProgressBar::CProgressBar()
{
	this->frame = Sprite::create(UIResources::Menus_LoadingMenu_LoadingFrame);
	this->progressBar = Sprite::create(UIResources::Menus_LoadingMenu_LoadingFrameFill);
	this->progressClip = ClippingRectangleNode::create(Rect(0, -32, this->progressBar->getContentSize().width, 64));
	
	this->setCascadeOpacityEnabled(true);
	this->progressClip->setCascadeOpacityEnabled(true);

	this->progressBar->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->progressClip->addChild(this->progressBar);
	this->setProgress(0.0f);

	this->addChild(this->frame);
	this->addChild(this->progressClip);
}

CProgressBar::~CProgressBar()
{
}

void CProgressBar::initializePositions()
{
	SmartNode::initializePositions();

	this->progressClip->setPosition(Vec2(-this->progressBar->getContentSize().width / 2, 0));
}

void CProgressBar::setProgress(float newProgress)
{
	if (newProgress < 0.0f)
	{
		newProgress = 0.0f;
	}
	else if (newProgress > 100.0f)
	{
		newProgress = 100.0f;
	}

	this->progress = newProgress;

	// Update progress bar
	Rect newClippingRegion = this->progressClip->getClippingRegion();
	newClippingRegion.size = Size(this->progressBar->getContentSize().width * this->progress, newClippingRegion.size.height);
	this->progressClip->setClippingRegion(newClippingRegion);
}
