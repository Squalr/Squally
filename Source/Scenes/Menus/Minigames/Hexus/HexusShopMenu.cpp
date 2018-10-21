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
	this->storeMenu = Sprite::create(Resources::Menus_StoreMenu_StoreBoard);

	this->jungleLootBoxButton = MenuSprite::create(Resources::Menus_StoreMenu_StoreOption, Resources::Menus_StoreMenu_StoreOptionSelected, Resources::Menus_StoreMenu_StoreOptionSelected);
	this->ruinsLootBoxButton = MenuSprite::create(Resources::Menus_StoreMenu_StoreOption, Resources::Menus_StoreMenu_StoreOptionSelected, Resources::Menus_StoreMenu_StoreOptionSelected);
	this->forestLootBoxButton = MenuSprite::create(Resources::Menus_StoreMenu_StoreOption, Resources::Menus_StoreMenu_StoreOptionSelected, Resources::Menus_StoreMenu_StoreOptionSelected);
	this->cavernsLootBoxButton = MenuSprite::create(Resources::Menus_StoreMenu_StoreOption, Resources::Menus_StoreMenu_StoreOptionSelected, Resources::Menus_StoreMenu_StoreOptionSelected);
	this->castleLootBoxButton = MenuSprite::create(Resources::Menus_StoreMenu_StoreOption, Resources::Menus_StoreMenu_StoreOptionSelected, Resources::Menus_StoreMenu_StoreOptionSelected);
	this->iceLootBoxButton = MenuSprite::create(Resources::Menus_StoreMenu_StoreOption, Resources::Menus_StoreMenu_StoreOptionSelected, Resources::Menus_StoreMenu_StoreOptionSelected);
	this->volcanoLootBoxButton = MenuSprite::create(Resources::Menus_StoreMenu_StoreOption, Resources::Menus_StoreMenu_StoreOptionSelected, Resources::Menus_StoreMenu_StoreOptionSelected);
	this->obeliskLootBoxButton = MenuSprite::create(Resources::Menus_StoreMenu_StoreOption, Resources::Menus_StoreMenu_StoreOptionSelected, Resources::Menus_StoreMenu_StoreOptionSelected);
	this->vaporLootBoxButton = MenuSprite::create(Resources::Menus_StoreMenu_StoreOption, Resources::Menus_StoreMenu_StoreOptionSelected, Resources::Menus_StoreMenu_StoreOptionSelected);

	Sprite* jungleLootBoxSprite = Sprite::create(Resources::Menus_StoreMenu_LootBoxes_JungleChestClosed);
	Sprite* ruinsLootBoxSprite = Sprite::create(Resources::Menus_StoreMenu_LootBoxes_RuinsChestClosed);
	Sprite* forestLootBoxSprite = Sprite::create(Resources::Menus_StoreMenu_LootBoxes_ForestChestClosed);
	Sprite* cavernsLootBoxSprite = Sprite::create(Resources::Menus_StoreMenu_LootBoxes_CavernsChestClosed);
	Sprite* castleLootBoxSprite = Sprite::create(Resources::Menus_StoreMenu_LootBoxes_CastleChestClosed);
	Sprite* iceLootBoxSprite = Sprite::create(Resources::Menus_StoreMenu_LootBoxes_IceChestClosed);
	Sprite* volcanoLootBoxSprite = Sprite::create(Resources::Menus_StoreMenu_LootBoxes_VolcanoChestClosed);
	Sprite* obeliskLootBoxSprite = Sprite::create(Resources::Menus_StoreMenu_LootBoxes_ObeliskChestClosed);
	Sprite* vaporLootBoxSprite = Sprite::create(Resources::Menus_StoreMenu_LootBoxes_VaporChestClosed);

	const float lootBoxScale = 0.33f;

	jungleLootBoxSprite->setScale(lootBoxScale);
	ruinsLootBoxSprite->setScale(lootBoxScale);
	forestLootBoxSprite->setScale(lootBoxScale);
	cavernsLootBoxSprite->setScale(lootBoxScale);
	castleLootBoxSprite->setScale(lootBoxScale);
	iceLootBoxSprite->setScale(lootBoxScale);
	volcanoLootBoxSprite->setScale(lootBoxScale);
	obeliskLootBoxSprite->setScale(lootBoxScale);
	vaporLootBoxSprite->setScale(lootBoxScale);

	this->jungleLootBoxButton->addChild(jungleLootBoxSprite);
	this->ruinsLootBoxButton->addChild(ruinsLootBoxSprite);
	this->forestLootBoxButton->addChild(forestLootBoxSprite);
	this->cavernsLootBoxButton->addChild(cavernsLootBoxSprite);
	this->castleLootBoxButton->addChild(castleLootBoxSprite);
	this->iceLootBoxButton->addChild(iceLootBoxSprite);
	this->volcanoLootBoxButton->addChild(volcanoLootBoxSprite);
	this->obeliskLootBoxButton->addChild(obeliskLootBoxSprite);
	this->vaporLootBoxButton->addChild(vaporLootBoxSprite);

	this->storeBack->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->storeFront->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->storeBack);
	this->addChild(this->shopKeeper);
	this->addChild(this->storeFront);
	this->addChild(this->storeMenu);
	this->addChild(this->jungleLootBoxButton);
	this->addChild(this->ruinsLootBoxButton);
	this->addChild(this->forestLootBoxButton);
	this->addChild(this->cavernsLootBoxButton);
	this->addChild(this->cavernsLootBoxButton);
	this->addChild(this->castleLootBoxButton);
	this->addChild(this->iceLootBoxButton);
	this->addChild(this->volcanoLootBoxButton);
	this->addChild(this->obeliskLootBoxButton);
	this->addChild(this->vaporLootBoxButton);
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
	this->storeMenu->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f, visibleSize.height / 2.0f));

	this->jungleLootBoxButton->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f - 288.0f, visibleSize.height / 2.0f + 224.0f));
	this->ruinsLootBoxButton->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f, visibleSize.height / 2.0f + 224.0f));
	this->forestLootBoxButton->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f + 288.0f, visibleSize.height / 2.0f + 224.0f));
	this->cavernsLootBoxButton->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f - 288.0f, visibleSize.height / 2.0f));
	this->castleLootBoxButton->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f, visibleSize.height / 2.0f));
	this->iceLootBoxButton->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f + 288.0f, visibleSize.height / 2.0f));
	this->volcanoLootBoxButton->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f - 288.0f, visibleSize.height / 2.0f - 224.0f));
	this->obeliskLootBoxButton->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f, visibleSize.height / 2.0f - 224.0f));
	this->vaporLootBoxButton->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f + 288.0f, visibleSize.height / 2.0f - 224.0f));
}
