#include "CSlider.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCClippingRectangleNode.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/UI/Controls/CProgressBar.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

CSlider* CSlider::create(std::string frameResource, std::string fillResource, std::string slideResource, std::string slideResourceSelected, float progress, bool isHorizontal)
{
	return CSlider::create(Sprite::create(frameResource), Sprite::create(fillResource), slideResource, slideResourceSelected, progress, isHorizontal);
}

CSlider* CSlider::create(Node* frame, Node* fill, std::string slideResource, std::string slideResourceSelected, float progress, bool isHorizontal)
{
	CSlider* instance = new CSlider(frame, fill, slideResource, slideResourceSelected, progress, isHorizontal);

	instance->autorelease();

	return instance;
}

CSlider::CSlider(Node* frame, Node* fill, std::string slideResource, std::string slideResourceSelected, float progress, bool isHorizontal)
{
	this->progress = progress;
	this->isHorizontal = isHorizontal;
	this->progressUpdateEvent = nullptr;
	this->progressBar = CProgressBar::create(frame, fill);
	this->progressBarHitBox = ClickableNode::create();
	this->slide = ClickableNode::create(slideResource, slideResourceSelected);

	this->setProgress(this->progress);

	this->progressBarHitBox->setContentSize(this->progressBar->getContentSize());
	this->progressBarHitBox->setMouseDownCallback(CC_CALLBACK_2(CSlider::onDrag, this));
	this->slide->setMouseDragCallback(CC_CALLBACK_2(CSlider::onDrag, this));

	this->progressBar->addChild(this->progressBarHitBox);
	this->addChild(this->progressBar);
	this->addChild(this->slide);
}

CSlider::~CSlider()
{
}

void CSlider::onEnter()
{
	super::onEnter();

	this->setProgress(progress);
}

void CSlider::initializePositions()
{
	super::initializePositions();

	this->updateSliderPosition();
}

void CSlider::setProgressUpdateCallback(std::function<void(float progress)> callback)
{
	this->progressUpdateEvent = callback;
}

void CSlider::updateSliderPosition()
{
	if (this->isHorizontal)
	{
		this->slide->setPosition(Vec2(this->progress * this->progressBar->getContentSize().width - this->progressBar->getContentSize().width / 2.0f, 0.0f));
	}
	else
	{
		this->slide->setPosition(Vec2(0.0f, this->progressBar->getContentSize().height / 2.0f - this->progress * this->progressBar->getContentSize().height));
	}
}

void CSlider::onDrag(ClickableNode* sprite, MouseEvents::MouseEventArgs* args)
{
	Vec2 thisPosition = GameUtils::getScreenBounds(this).origin;

	if (this->isHorizontal)
	{
		float newX = MathUtils::clamp(args->mouseCoords.x - thisPosition.x, -this->progressBar->getContentSize().width / 2.0f, this->progressBar->getContentSize().width / 2.0f);
		Vec2 newPosition = Vec2(newX, thisPosition.y);

		this->setProgress((newPosition.x + this->progressBar->getContentSize().width / 2.0f) / this->progressBar->getContentSize().width);
	}
	else
	{
		float newY = MathUtils::clamp(args->mouseCoords.y - thisPosition.y, -this->progressBar->getContentSize().height / 2.0f, this->progressBar->getContentSize().height / 2.0f);
		Vec2 newPosition = Vec2(thisPosition.x, newY);

		this->setProgress(1.0f - (newPosition.y + this->progressBar->getContentSize().height / 2.0f) / this->progressBar->getContentSize().height);
	}

	this->updateSliderPosition();
}

void CSlider::setProgress(float newProgress)
{
	this->progress = MathUtils::clamp(newProgress, 0.0f, 1.0f);

	this->progressBar->setProgress(this->progress);

	if (this->progressUpdateEvent != nullptr)
	{
		this->progressUpdateEvent(this->progress);
	}
}
