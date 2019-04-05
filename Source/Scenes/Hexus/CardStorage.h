#pragma once
#include <map>
#include <string>
#include <vector>

#include "Engine/Save/SaveManager.h"

class CardData;

class CardStorage
{
public:
	static CardStorage* getInstance();

	static void saveGold(int value);
	static void addGold(int value);
	static void saveStorageCards(std::vector<CardData*> storageCards);
	static void saveStorageCardsByCount(std::map<CardData*, int> storageCards);
	static void saveDeckCards(std::vector<CardData*> deckCards);
	static void saveDeckCardsByCount(std::map<CardData*, int> storageCards);
	static void addStorageCard(CardData* cardData);
	static int getGold();
	static std::vector<CardData*> getStorageCards();
	static std::map<CardData*, int> getStorageCardsByCount();
	static std::vector<CardData*> getDeckCards();
	static std::map<CardData*, int> getDeckCardsByCount();
	static int getOwnedCardCount(CardData* cardData);

	static const int minimumDeckCards;

private:
	CardStorage();
	~CardStorage();

	std::vector<CardData*> defaultCards;
	std::vector<CardData*> defaultStorageCards;
	static const std::string SaveKeyStorageCards;
	static const std::string SaveKeyDeckCards;
	static const std::string SaveKeyGold;
	static CardStorage* instance;
};

