#pragma once
#include <math.h>
#include "cocos2d.h"

#include "Engine/SmartScene.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Special/Shopkeeper.h"
#include "Events/HexusEvents.h"
#include "Events/NavigationEvents.h"
#include "Menus/Minigames/Hexus/MenuCard.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/CardStorage.h"

using namespace cocos2d;

class HexusStoreMenu : public SmartScene
{
public:
	static HexusStoreMenu * create();

protected:
	HexusStoreMenu();
	~HexusStoreMenu();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	std::tuple<MenuSprite*, int> constructLootBoxButton(std::string lootBoxAnimations, int price, std::map<CardData*, float> cardChoices);
	std::tuple<MenuSprite*, MenuCard*, int> constructCard(CardData* cardData);
	void onLootBoxTabClick();
	void onBinaryTabClick();
	void onDecimalTabClick();
	void onHexTabClick();
	void onSpecialTabClick();
	void updateAllCardLimits();
	void updateCardLimitText(Label* label, CardData* cardData);
	void updateGoldText();
	void hideMenus();
	void onLootBoxClick(MenuSprite* sprite, int price, std::map<CardData*, float> cardChoices, AnimationNode* animationNode, SpriterEngine::EntityInstance* entity);
	void onCardClick(MenuSprite* card, CardData* cardData, int price, Label* label);
	void onBackClick(MenuSprite* menuSprite);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onLootBoxReturnButtonClick(int price, std::vector<Card*> chosenCards);
	static CardData* chooseRandomCard(std::map<CardData*, float> cardChoices);
	static std::map<CardData*, float> getCardsTier1();
	static std::map<CardData*, float> getCardsTier2();
	static std::map<CardData*, float> getCardsTier3();
	static std::map<CardData*, float> getCardsTier4();
	static std::map<CardData*, float> getCardsTier5();
	static std::map<CardData*, float> getCardsTier6();
	static std::map<CardData*, float> getCardsTier7();
	static std::map<CardData*, float> getCardsTier8();
	static std::map<CardData*, float> getCardsTier9();

	ParticleSystem* dustParticles;
	Sprite* storeBack;
	Shopkeeper* shopKeeper;
	Sprite* storeFront;
	Node* storeNode;
	Sprite* storeMenu;
	Sprite* goldPanel;
	Sprite* goldIcon;
	Label* goldLabel;
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
	TextMenuSprite* backButton;
	LayerColor* lootBoxRewardBackground;
	MenuSprite* lootBoxReturnButton;
	Node* chosenCardsNode;

	std::vector<std::tuple<MenuSprite*, int>> lootBoxes;
	std::vector<std::tuple<MenuSprite*, MenuCard*, int>> binaryCards;
	std::vector<std::tuple<MenuSprite*, MenuCard*, int>> decimalCards;
	std::vector<std::tuple<MenuSprite*, MenuCard*, int>> hexCards;
	std::vector<std::tuple<MenuSprite*, MenuCard*, int>> specialCards;
	std::map<MenuCard*, Label*> limitLabels;

	static const float lootBoxScale;
};
