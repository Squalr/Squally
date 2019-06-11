#include "ProgressBar.h"

#include "cocos/2d/CCClippingNode.h"
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

	this->clipStencil = DrawNode::create();
	this->progressClip = ClippingNode::create(clipStencil);

	this->progressClip->setPosition(Vec2(fillOffset.x, fillOffset.y));
	this->setProgress(0.0f);

	this->setContentSize(this->frame->getContentSize());

	this->progressClip->addChild(this->progressBar);
	this->addChild(this->frame);
	this->addChild(this->progressClip);

	// Enable to debug clipping:
	// this->addChild(clipStencil);
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

	if (this->clipStencil != nullptr)
	{
		// Update progress bar
		this->clipStencil->clear();

		if (this->isHorizontal)
		{
			this->clipStencil->drawSolidRect(
				-Vec2(this->progressBar->getContentSize() / 2.0f),
				Size(this->progressBar->getContentSize().width * this->progress, this->progressBar->getContentSize().height) - this->progressBar->getContentSize() / 2.0f,
				Color4F::GREEN
			);
		}
		else
		{
			this->clipStencil->drawSolidRect(
				-Vec2(this->progressBar->getContentSize() / 2.0f),
				Size(this->progressBar->getContentSize().width, this->progressBar->getContentSize().height * this->progress) - this->progressBar->getContentSize() / 2.0f,
				Color4F::GREEN
			);
		}
	}
}
