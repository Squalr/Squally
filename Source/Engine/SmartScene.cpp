#include "SmartScene.h"

#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListener.h"
const float SmartScene::defaultFadeSpeed = 0.75f;

using namespace cocos2d;

SmartScene::SmartScene()
{
	this->fadeAction = nullptr;
	this->fadeSpeed = SmartScene::defaultFadeSpeed;
	this->layerColor = LayerColor::create(Color4B(0, 0, 0, 255));

	this->addChild(this->layerColor);
}

SmartScene::~SmartScene()
{
}

void SmartScene::onEnter()
{
	Scene::onEnter();

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

	this->initializePositions();
	this->initializeListeners();
}

void SmartScene::initializePositions()
{
}

void SmartScene::initializeListeners()
{
	this->removeAllListeners();
}

void SmartScene::removeAllListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void SmartScene::addEventListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void SmartScene::addEventListenerIgnorePause(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	listener->setIgnorePause(true);

	this->addEventListener(listener);
}

void SmartScene::resume()
{
	Scene::resume();

	this->initializeListeners();
}


void SmartScene::setFadeSpeed(float newFadeSpeed)
{
	this->fadeSpeed = newFadeSpeed;
}

float SmartScene::getFadeSpeed()
{
	return this->fadeSpeed;
}

void SmartScene::pause()
{
	// On pause cancel the fade in animation
	if (this->fadeAction != nullptr)
	{
		this->stopAction(this->fadeAction);
		this->layerColor->setOpacity(0.0f);
	}

	Scene::pause();
}
