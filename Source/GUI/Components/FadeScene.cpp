#include "FadeScene.h"

FadeScene::FadeScene()
{
	this->layerColor = LayerColor::create(Color4B(0, 0, 0, 255));

	this->addChild(this->layerColor);
}

FadeScene::~FadeScene()
{
}

void FadeScene::onEnter()
{
	this->layerColor->setOpacity(255);
	this->layerColor->setZOrder(999);

	Scene::onEnter();

	this->layerColor->runAction(FadeOut::create(1.0f));
}
