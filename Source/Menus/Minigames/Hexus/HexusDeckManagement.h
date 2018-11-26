#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Engine/UI/Controls/CCheckbox.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Controls/ToggleGroup.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Minigames/Hexus/MenuCard.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/CardStorage.h"

using namespace cocos2d;

class HexusDeckManagement : public FadeScene
{
public:
	static HexusDeckManagement * create();

protected:
	HexusDeckManagement();
	~HexusDeckManagement();

private:
	enum CardFilterFlags
	{
		Special = 1 << 0,
		Binary = 1 << 1,
		Decimal = 1 << 2,
		Hex = 1 << 3,
		All = Special | Binary | Decimal | Hex
	};

	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onBackClick(MenuSprite* menuSprite);
	void onToggleSelect(CCheckbox* activeToggle);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void rebuildCardLists();
	void rebuildCardList(std::map<CardData*, int> cards, std::map<CardData*, MenuCard*> displayCards);
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
	TextMenuSprite* backButton;
	CCheckbox* allButton;
	CCheckbox* specialButton;
	CCheckbox* binaryButton;
	CCheckbox* decimalButton;
	CCheckbox* hexButton;
	ToggleGroup* filters;

	Label* totalCardsInDeckLabel;
	Label* totalCardsInDeckValueLabel;
	Label* binaryCardsInDeckLabel;
	Label* binaryCardsInDeckValueLabel;
	Label* decimalCardsInDeckLabel;
	Label* decimalCardsInDeckValueLabel;
	Label* hexCardsInDeckLabel;
	Label* hexCardsInDeckValueLabel;
	Label* specialCardsInDeckLabel;
	Label* specialCardsInDeckValueLabel;

	CardFilterFlags activeFilter;

	std::map<CardData*, MenuCard*> displayDeckCards;
	std::map<CardData*, MenuCard*> displayStorageCards;
	std::map<MenuCard*, Label*> countLabels;

	std::map<CardData*, int> deckCards;
	std::map<CardData*, int> storageCards;
};
