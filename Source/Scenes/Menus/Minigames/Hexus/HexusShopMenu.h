#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Special/Shopkeeper.h"
#include "Events/HexusEvents.h"
#include "Events/NavigationEvents.h"
#include "Resources.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/CardStorage.h"

using namespace cocos2d;

class HexusShopMenu : public FadeScene
{
public:
	static HexusShopMenu * create();

protected:
	HexusShopMenu();
	~HexusShopMenu();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	Sprite* storeBack;
	Shopkeeper* shopKeeper;
	Sprite* storeFront;
	Sprite* storeMenu;
	MenuSprite* jungleLootBoxButton;
	MenuSprite* ruinsLootBoxButton;
	MenuSprite* forestLootBoxButton;
	MenuSprite* cavernsLootBoxButton;
	MenuSprite* castleLootBoxButton;
	MenuSprite* iceLootBoxButton;
	MenuSprite* volcanoLootBoxButton;
	MenuSprite* obeliskLootBoxButton;
	MenuSprite* vaporLootBoxButton;
};
