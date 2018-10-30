#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/CardStorage.h"
#include "Scenes/Menus/Minigames/Hexus/MenuCard.h"

using namespace cocos2d;

class HexusDeckManagement : public FadeScene
{
public:
	static HexusDeckManagement * create();

protected:
	HexusDeckManagement();
	~HexusDeckManagement();

private:
	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onBackClick(MenuSprite* menuSprite);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void rebuildCardLists();
	void rebuildDeckCards();
	void rebuildStorageCards();
	void save(bool exit);
	MenuCard* createCard(CardData* cardData, int count);
	void updateCardCount(MenuCard* card, int count);

	void onDeckCardClick(Card* card);
	void onStorageCardClick(Card* card);
	void onDeckCardMouseOver(Card* card);
	void onStorageCardMouseOver(Card* card);

	Sprite* background;
	ScrollPane* storageScrollPane;
	ScrollPane* deckScrollPane;
	Sprite* storageSprite;
	Label* storageLabel;
	Sprite* deckSprite;
	Label* deckLabel;
	Sprite* titleSprite;
	Label* cardManagementLabel;
	TextMenuSprite* backButton;

	Label* cardsInDeckLabel;
	Label* cardsInDeckValueLabel;

	std::map<CardData*, MenuCard*> displayDeckCards;
	std::map<CardData*, MenuCard*> displayStorageCards;
	std::map<MenuCard*, Label*> countLabels;

	std::map<CardData*, int> deckCards;
	std::map<CardData*, int> storageCards;
};
