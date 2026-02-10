#include "OptionsScene.h"

#include "2d/CCNode.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Menus/Options/OptionsMenu.h"
#include "Menus/MenuBackground.h"
#include "Scenes/Title/TitleScreen.h"

using namespace cocos2d;

OptionsScene* OptionsScene::Instance;

OptionsScene* OptionsScene::getInstance()
{
	if (OptionsScene::Instance == nullptr)
	{
		OptionsScene::Instance = new OptionsScene();

		OptionsScene::Instance->autorelease();
		OptionsScene::Instance->initializeListeners();
		GlobalDirector::RegisterGlobalScene(OptionsScene::Instance);
	}

	return OptionsScene::Instance;
}

OptionsScene::OptionsScene()
{
	this->menu = OptionsMenu::create(true);
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
		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]() { return TitleScreen::getInstance(); }));
	});
}
