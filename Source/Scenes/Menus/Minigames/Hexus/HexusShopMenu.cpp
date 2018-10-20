#include "HexusShopMenu.h"

HexusShopMenu * HexusShopMenu::create()
{
	HexusShopMenu* instance = new HexusShopMenu();

	instance->autorelease();

	return instance;
}

HexusShopMenu::HexusShopMenu()
{
	this->storeBack = Sprite::create(Resources::Menus_StoreMenu_StoreBack);
	this->shopKeeper = Shopkeeper::create();
	this->storeFront = Sprite::create(Resources::Menus_StoreMenu_Store);

	this->storeBack->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->storeFront->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->storeBack);
	this->addChild(this->shopKeeper);
	this->addChild(this->storeFront);
	this->addChild(Mouse::create());
}

HexusShopMenu::~HexusShopMenu()
{
}

void HexusShopMenu::onEnter()
{
	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;
}

void HexusShopMenu::initializeListeners()
{
	FadeScene::initializeListeners();
}

void HexusShopMenu::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->storeBack->setPosition(Vec2(0.0f, visibleSize.height / 2.0f + 144.0f));
	this->shopKeeper->setPosition(Vec2(visibleSize.width / 2.0f - 680.0f, visibleSize.height / 2.0f));
	this->storeFront->setPosition(Vec2(0.0f, visibleSize.height / 2.0f - 176.0f));
}
