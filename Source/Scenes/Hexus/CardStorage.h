#pragma once
#include "cocos2d.h"

#include "Engine/Save/SaveManager.h"
#include "Resources.h"
#include "Scenes/Hexus/CardData/CardList.h"

using namespace cocos2d;

class CardStorage
{
public:
	static CardStorage * getInstance();

	static void saveGold(int value);
	static void addGold(int value);
	static void saveStorageCards(std::vector<CardData*> storageCards);
	static void saveDeckCards(std::vector<CardData*> deckCards);
	static void addStorageCard(CardData* cardData);
	static int getGold();
	static std::vector<CardData*> getStorageCards();
	static std::vector<CardData*> getDeckCards();
	static int getOwnedCardCount(CardData* cardData);

	static const int minimumDeckCards;

private:
	CardStorage();
	~CardStorage();

	std::vector<CardData*> defaultCards;
	static const std::string SaveKeyStorageCards;
	static const std::string SaveKeyDeckCards;
	static const std::string SaveKeyGold;
	static CardStorage* instance;
};

