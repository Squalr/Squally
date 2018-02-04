#include "FadeScene.h"

FadeScene::FadeScene()
{
	this->fadeAction = nullptr;
	this->layerColor = LayerColor::create(Color4B(0, 0, 0, 255));

	this->addChild(this->layerColor);
}

FadeScene::~FadeScene()
{
}

void FadeScene::onEnter()
{
	Scene::onEnter();

	// Make fade in visible, fullscreen, and topmost
	this->layerColor->setContentSize(Director::getInstance()->getOpenGLView()->getDesignResolutionSize());
	this->layerColor->setOpacity(255);
	this->layerColor->setZOrder(999);

	// Fade into the scene
	this->fadeAction = FadeOut::create(0.75f);
	this->layerColor->runAction(this->fadeAction);
}

void FadeScene::pause()
{
	// On pause cancel the fade in animation
	if (this->fadeAction != nullptr)
	{
		this->stopAction(this->fadeAction);
		this->layerColor->setOpacity(0.0f);
	}

	Scene::pause();
}
