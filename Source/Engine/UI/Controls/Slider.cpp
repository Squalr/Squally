#include "Slider.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

Slider* Slider::create(std::string frameResource, std::string fillResource, std::string slideResource, std::string slideResourceSelected, float progress, bool isHorizontal)
{
	return Slider::create(Sprite::create(frameResource), Sprite::create(fillResource), slideResource, slideResourceSelected, progress, isHorizontal);
}

Slider* Slider::create(Node* frame, Node* fill, std::string slideResource, std::string slideResourceSelected, float progress, bool isHorizontal)
{
	Slider* instance = new Slider(frame, fill, slideResource, slideResourceSelected, progress, isHorizontal);

	instance->autorelease();

	return instance;
}

Slider::Slider(Node* frame, Node* fill, std::string slideResource, std::string slideResourceSelected, float progress, bool isHorizontal)
{
	this->progress = progress;
	this->isHorizontal = isHorizontal;
	this->progressUpdateEvent = nullptr;
	this->progressBar = ProgressBar::create(frame, fill);
	this->progressBarHitBox = ClickableNode::create();
	this->slide = ClickableNode::create(slideResource, slideResourceSelected);

	this->setProgress(this->progress);

	this->progressBarHitBox->setContentSize(this->progressBar->getContentSize());
	this->progressBarHitBox->setMouseDownCallback(CC_CALLBACK_1(Slider::onDrag, this));
	this->progressBarHitBox->setMouseDragCallback(CC_CALLBACK_1(Slider::onDrag, this));
	this->slide->setMouseDragCallback(CC_CALLBACK_1(Slider::onDrag, this));

	this->progressBar->addChild(this->progressBarHitBox);
	this->addChild(this->progressBar);
	this->addChild(this->slide);
}

Slider::~Slider()
{
}

void Slider::onEnter()
{
	super::onEnter();

	this->setProgress(progress);
}

void Slider::initializePositions()
{
	super::initializePositions();

	this->updateSliderPosition();
}

void Slider::setProgressUpdateCallback(std::function<void(float progress)> callback)
{
	this->progressUpdateEvent = callback;
}

void Slider::updateSliderPosition()
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

void Slider::onDrag(MouseEvents::MouseEventArgs* args)
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
}

void Slider::setProgress(float newProgress)
{
	this->progress = MathUtils::clamp(newProgress, 0.0f, 1.0f);

	this->progressBar->setProgress(this->progress);

	if (this->progressUpdateEvent != nullptr)
	{
		this->progressUpdateEvent(this->progress);
	}

	this->updateSliderPosition();
}
