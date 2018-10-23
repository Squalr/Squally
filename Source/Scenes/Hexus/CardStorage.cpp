#include "CardStorage.h"

const std::string CardStorage::SaveKeyStorageCards = "SAVE_KEY_STORAGE_CARDS";
const std::string CardStorage::SaveKeyDeckCards = "SAVE_KEY_DECK_CARDS";
const std::string CardStorage::SaveKeyGold = "SAVE_KEY_GOLD";

const int CardStorage::minimumDeckCards = 20;

CardStorage* CardStorage::instance = nullptr;

CardStorage* CardStorage::getInstance()
{
	if (CardStorage::instance == nullptr)
	{
		CardStorage::instance = new CardStorage();
	}

	return CardStorage::instance;
}

CardStorage::CardStorage()
{
	this->defaultCards = std::vector<CardData*>();

	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary0));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary1));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal0));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal1));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal1));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal2));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal3));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal3));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal4));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex0));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex1));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex2));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex2));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex3));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex3));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex4));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex4));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Addition));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Addition));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft));
	this->defaultCards.push_back(CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft));
}

CardStorage::~CardStorage()
{
}

void CardStorage::saveGold(int value)
{
	SaveManager::saveGlobalData(CardStorage::SaveKeyGold, cocos2d::Value(value));
}


int CardStorage::getGold()
{
	return SaveManager::getGlobalDataOrDefault(CardStorage::SaveKeyGold, cocos2d::Value(0)).asInt();
}

void CardStorage::saveDeckCards(std::vector<CardData*> deckCards)
{
	ValueVector deckCardsValueVector = ValueVector();

	for (auto it = deckCards.begin(); it != deckCards.end(); it++)
	{
		deckCardsValueVector.push_back(Value((*it)->cardName));
	}

	SaveManager::saveGlobalData(CardStorage::SaveKeyDeckCards, cocos2d::Value(deckCardsValueVector));
}

void CardStorage::addStorageCard(CardData* cardData)
{
	if (CardStorage::getOwnedCardCount(cardData) >= 3)
	{
		return;
	}

	std::vector<CardData*> storageCards = CardStorage::getStorageCards();

	storageCards.push_back(cardData);

	CardStorage::saveStorageCards(storageCards);
}

std::vector<CardData*> CardStorage::getDeckCards()
{
	CardStorage* instance = CardStorage::getInstance();

	std::vector<CardData*> deckCards = std::vector<CardData*>();

	if (SaveManager::hasGlobalData(CardStorage::SaveKeyDeckCards))
	{
		ValueVector savedCards = SaveManager::getGlobalData(CardStorage::SaveKeyDeckCards).asValueVector();

		for (auto it = savedCards.begin(); it != savedCards.end(); it++)
		{
			std::string cardKey = it->asString();

			if (CardList::getInstance()->cardListByName->find(cardKey) != CardList::getInstance()->cardListByName->end())
			{
				CardData* nextCard = CardList::getInstance()->cardListByName->at(cardKey);

				deckCards.push_back(nextCard);
			}
		}
	}
	else
	{
		return instance->defaultCards;
	}

	return deckCards;
}

void CardStorage::saveStorageCards(std::vector<CardData*> storageCards)
{
	ValueVector storageCardsValueVector = ValueVector();

	for (auto it = storageCards.begin(); it != storageCards.end(); it++)
	{
		storageCardsValueVector.push_back(Value((*it)->cardName));
	}

	SaveManager::saveGlobalData(CardStorage::SaveKeyStorageCards, cocos2d::Value(storageCardsValueVector));
}

std::vector<CardData*> CardStorage::getStorageCards()
{
	CardStorage* instance = CardStorage::getInstance();

	std::vector<CardData*> storageCards = std::vector<CardData*>();

	if (SaveManager::hasGlobalData(CardStorage::SaveKeyStorageCards))
	{
		ValueVector savedCards = SaveManager::getGlobalData(CardStorage::SaveKeyStorageCards).asValueVector();

		for (auto it = savedCards.begin(); it != savedCards.end(); it++)
		{
			std::string cardKey = it->asString();

			if (CardList::getInstance()->cardListByName->find(cardKey) != CardList::getInstance()->cardListByName->end())
			{
				CardData* nextCard = CardList::getInstance()->cardListByName->at(cardKey);

				storageCards.push_back(nextCard);
			}
		}
	}

	return storageCards;
}

int CardStorage::getOwnedCardCount(CardData* cardData)
{
	int count = 0;

	std::vector<CardData*> deck = CardStorage::getDeckCards();
	std::vector<CardData*> storage = CardStorage::getStorageCards();

	for (auto it = deck.begin(); it != deck.end(); it++)
	{
		if ((*it)->cardName == cardData->cardName)
		{
			count++;
		}
	}

	for (auto it = storage.begin(); it != storage.end(); it++)
	{
		if ((*it)->cardName == cardData->cardName)
		{
			count++;
		}
	}

	return count;
}
