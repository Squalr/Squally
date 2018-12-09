#include "FadeScene.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"

using namespace cocos2d;

const float FadeScene::defaultFadeSpeed = 0.75f;

FadeScene::FadeScene()
{
	this->fadeAction = nullptr;
	this->fadeSpeed = FadeScene::defaultFadeSpeed;
	this->layerColor = LayerColor::create(Color4B(0, 0, 0, 255));

	this->addChild(this->layerColor);
}

FadeScene::~FadeScene()
{
}

void FadeScene::setFadeSpeed(float newFadeSpeed)
{
	this->fadeSpeed = newFadeSpeed;
}

float FadeScene::getFadeSpeed()
{
	return this->fadeSpeed;
}

void FadeScene::onEnter()
{
	SmartScene::onEnter();

	// Make fade in visible, fullscreen, and topmost
	if (this->fadeSpeed > 0.0f)
	{
		this->layerColor->setContentSize(Director::getInstance()->getOpenGLView()->getDesignResolutionSize());
		this->layerColor->setOpacity(255);

		// Fade into the scene
		this->fadeAction = FadeOut::create(this->fadeSpeed);
		this->layerColor->runAction(this->fadeAction);
	}
	else
	{
		this->layerColor->setOpacity(0);
	}

	this->layerColor->setZOrder(999);
}

void FadeScene::pause()
{
	// On pause cancel the fade in animation
	if (this->fadeAction != nullptr)
	{
		this->stopAction(this->fadeAction);
		this->layerColor->setOpacity(0.0f);
	}

	SmartScene::pause();
}
