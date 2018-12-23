#pragma once
#include <map>
#include <vector>

class CardData;

class CardList
{
public:
	static CardList* getInstance();

	std::map<std::string, CardData*> cardListByName;
	std::vector<CardData*> sortedCardList;
	
protected:
	CardList();
	~CardList();

private:

	static CardList* instance;
};

