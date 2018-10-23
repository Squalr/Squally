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
	MenuSprite* constructLootBoxButton(std::string lootBoxIcon, int price);
	Card* constructCard(CardData* cardData, int price);
	void onLootBoxTabClick();
	void onBinaryTabClick();
	void onDecimalTabClick();
	void onHexTabClick();
	void onSpecialTabClick();
	void resetMenus();
	void onLootBoxClick(MenuSprite* sprite, int price);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	Sprite* storeBack;
	Shopkeeper* shopKeeper;
	Sprite* storeFront;
	Node* storeNode;
	Sprite* storeMenu;
	Node* lootboxesNode;
	ScrollPane* binaryCardsScrollPane;
	ScrollPane* decimalCardsScrollPane;
	ScrollPane* hexCardsScrollPane;
	ScrollPane* specialCardsScrollPane;
	MenuSprite* lootBoxButton;
	MenuSprite* binaryButton;
	MenuSprite* decimalButton;
	MenuSprite* hexButton;
	MenuSprite* specialButton;
	Label* storeLabel;

	std::vector<MenuSprite*> lootBoxes;
	std::map<int, Card*> binaryCards;
	std::map<int, Card*> decimalCards;
	std::map<int, Card*> hexCards;
	std::vector<Card*> specialCards;

	static const float lootBoxScale;
};
