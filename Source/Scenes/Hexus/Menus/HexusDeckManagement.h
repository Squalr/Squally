#pragma once
#include <map>

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Sprite;
}

class Card;
class CardData;
class Checkbox;
class ClickableNode;
class ClickableTextNode;
class ConstantString;
class LocalizedLabel;
class MenuCard;
class ToggleGroup;
class ScrollPane;
class Sound;

class HexusDeckManagement : public GlobalScene
{
public:
	static HexusDeckManagement* getInstance();

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
	void onBackClick();
	void onToggleSelect(Checkbox* activeToggle);
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
	ClickableTextNode* backButton;
	Checkbox* allButton;
	Checkbox* specialButton;
	Checkbox* binaryButton;
	Checkbox* decimalButton;
	Checkbox* hexButton;
	ToggleGroup* filters;

	LocalizedLabel* totalCardsInDeckLabel;
	ConstantString* totalCardsInDeckValueXString;
	ConstantString* totalCardsInDeckValueYString;
	LocalizedLabel* totalCardsInDeckValueLabel;
	LocalizedLabel* binaryCardsInDeckLabel;
	ConstantString* binaryCardsInDeckValueString;
	LocalizedLabel* binaryCardsInDeckValueLabel;
	LocalizedLabel* decimalCardsInDeckLabel;
	ConstantString* decimalCardsInDeckValueString;
	LocalizedLabel* decimalCardsInDeckValueLabel;
	LocalizedLabel* hexCardsInDeckLabel;
	ConstantString* hexCardsInDeckValueString;
	LocalizedLabel* hexCardsInDeckValueLabel;
	LocalizedLabel* specialCardsInDeckLabel;
	ConstantString* specialCardsInDeckValueString;
	LocalizedLabel* specialCardsInDeckValueLabel;

	CardFilterFlags activeFilter;

	std::map<CardData*, MenuCard*> displayDeckCards;
	std::map<CardData*, MenuCard*> displayStorageCards;
	std::map<MenuCard*, std::tuple<ConstantString*, LocalizedLabel*>> countLabels;

	std::map<CardData*, int> deckCards;
	std::map<CardData*, int> storageCards;

	Sound* cardMovementSound;
	
	static HexusDeckManagement* instance;
};
