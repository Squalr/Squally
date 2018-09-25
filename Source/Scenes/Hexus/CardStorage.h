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

	static void saveStorageCards(std::vector<CardData*> storageCards);
	static void saveDeckCards(std::vector<CardData*> deckCards);
	static std::vector<CardData*> getStorageCards();
	static std::vector<CardData*> getDeckCards();

private:
	CardStorage();
	~CardStorage();

	std::vector<CardData*> defaultCards;
	static const std::string SaveKeyStorageCards;
	static const std::string SaveKeyDeckCards;
	static CardStorage* instance;
};

