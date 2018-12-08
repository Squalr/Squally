#include "OptionsScene.h"

OptionsScene* OptionsScene::instance;

void OptionsScene::registerGlobalScene()
{
	if (OptionsScene::instance == nullptr)
	{
		OptionsScene::instance = new OptionsScene();

		OptionsScene::instance->autorelease();
		OptionsScene::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(OptionsScene::instance);
}

OptionsScene::OptionsScene()
{
	this->menu = OptionsMenu::create();
	this->backgroundNode = Node::create();

	this->addChild(this->backgroundNode);
	this->addChild(this->menu);

	this->setFadeSpeed(0.0f);
}

OptionsScene::~OptionsScene()
{
}

void OptionsScene::onEnter()
{
	GlobalScene::onEnter();

	this->backgroundNode->addChild(MenuBackground::claimInstance());
}

void OptionsScene::initializePositions()
{
	GlobalScene::initializePositions();
}

void OptionsScene::initializeListeners()
{
	GlobalScene::initializeListeners();

	instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateOptions, [](EventCustom* args)
	{
		GlobalDirector::loadScene(OptionsScene::instance);
	}));
}
