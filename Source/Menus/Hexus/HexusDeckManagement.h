#pragma once
#include <map>

#include "cocos/base/CCEventKeyboard.h"

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Sprite;
}

class Card;
class CardData;
class CCheckbox;
class LocalizedLabel;
class MenuCard;
class MenuSprite;
class TextMenuSprite;
class ToggleGroup;
class ScrollPane;

class HexusDeckManagement : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	HexusDeckManagement();
	~HexusDeckManagement();

private:
	typedef GlobalScene super;
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
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void rebuildCardLists();
	void rebuildCardList(std::map<CardData*, int> cards, std::map<CardData*, MenuCard*> displayCards);
	void save(bool exit);
	MenuCard* createCard(CardData* cardData, int count);
	void updateCardCount(MenuCard* card, int count);

	void onDeckCardClick(Card* card);
	void onStorageCardClick(Card* card);
	void onDeckCardMouseOver(Card* card);
	void onStorageCardMouseOver(Card* card);

	cocos2d::Sprite* background;
	ScrollPane* storageScrollPane;
	ScrollPane* deckScrollPane;
	cocos2d::Sprite* storageSprite;
	LocalizedLabel* storageLabel;
	cocos2d::Sprite* deckSprite;
	LocalizedLabel* deckLabel;
	cocos2d::Sprite* titleSprite;
	TextMenuSprite* backButton;
	CCheckbox* allButton;
	CCheckbox* specialButton;
	CCheckbox* binaryButton;
	CCheckbox* decimalButton;
	CCheckbox* hexButton;
	ToggleGroup* filters;

	LocalizedLabel* totalCardsInDeckLabel;
	LocalizedLabel* totalCardsInDeckValueLabel;
	LocalizedLabel* binaryCardsInDeckLabel;
	LocalizedLabel* binaryCardsInDeckValueLabel;
	LocalizedLabel* decimalCardsInDeckLabel;
	LocalizedLabel* decimalCardsInDeckValueLabel;
	LocalizedLabel* hexCardsInDeckLabel;
	LocalizedLabel* hexCardsInDeckValueLabel;
	LocalizedLabel* specialCardsInDeckLabel;
	LocalizedLabel* specialCardsInDeckValueLabel;

	CardFilterFlags activeFilter;

	std::map<CardData*, MenuCard*> displayDeckCards;
	std::map<CardData*, MenuCard*> displayStorageCards;
	std::map<MenuCard*, LocalizedLabel*> countLabels;

	std::map<CardData*, int> deckCards;
	std::map<CardData*, int> storageCards;
	
	static HexusDeckManagement* instance;
};
