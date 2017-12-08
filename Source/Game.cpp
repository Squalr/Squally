#include "Game.h"
#include "SimpleAudioEngine.h"
#include "Resources.h"
#include "Level/Level.h"

using namespace cocos2d;

// on "init" you need to initialize your instance
bool Game::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	MenuItemImage* closeItem = MenuItemImage::create(Resources::CloseNormal, Resources::CloseSelected, CC_CALLBACK_1(Game::menuCloseCallback, this));

	float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
	float y = origin.y + closeItem->getContentSize().height / 2;

	closeItem->setPosition(Vec2(x, y));

	// create menu, it's an autorelease object
	Menu* menu = Menu::create(closeItem, NULL);

	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	Label* label = Label::createWithTTF("Squalr Tutorial", Resources::Fonts_Marker_Felt, 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	Level* level = new Level();
	level->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(level, 0);

	return true;
}

Scene* Game::createScene()
{
	return Game::create();
}

void Game::menuCloseCallback(Ref* pSender)
{
	// Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}
