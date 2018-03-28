#include "CProgressBar.h"

CProgressBar* CProgressBar::create()
{
	CProgressBar* progressBar = new CProgressBar();

	progressBar->autorelease();

	return progressBar;
}

CProgressBar::CProgressBar()
{
	this->frame = Sprite::create(Resources::Menus_LoadingMenu_LoadingFrame);
	this->progressBar = Sprite::create(Resources::Menus_LoadingMenu_LoadingFrameFill);
	this->progressClip = ClippingRectangleNode::create(Rect(0, -32, this->progressBar->getContentSize().width, 64));
	
	this->setCascadeOpacityEnabled(true);
	this->progressClip->setCascadeOpacityEnabled(true);

	this->progressBar->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->progressClip->addChild(this->progressBar);

	this->addChild(this->frame);
	this->addChild(this->progressClip);

	this->initializePositions();
}

CProgressBar::~CProgressBar()
{
}

void CProgressBar::initializePositions()
{
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
