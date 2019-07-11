#include "OptionsScene.h"

#include "cocos/2d/CCNode.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Menus/Options/OptionsMenu.h"
#include "Menus/MenuBackground.h"
#include "Scenes/Title/TitleScreen.h"

using namespace cocos2d;

OptionsScene* OptionsScene::instance;

OptionsScene* OptionsScene::getInstance()
{
	if (OptionsScene::instance == nullptr)
	{
		OptionsScene::instance = new OptionsScene();

		OptionsScene::instance->autorelease();
		OptionsScene::instance->initializeListeners();
		GlobalDirector::registerGlobalScene(OptionsScene::instance);
	}

	return OptionsScene::instance;
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
	super::onEnter();

	this->backgroundNode->addChild(MenuBackground::claimInstance());
}

void OptionsScene::initializePositions()
{
	super::initializePositions();
}

void OptionsScene::initializeListeners()
{
	super::initializeListeners();

	this->menu->setBackClickCallback([]()
	{
		NavigationEvents::LoadScene(TitleScreen::getInstance());
	});
}
