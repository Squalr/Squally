#pragma once

#include <string>
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
	virtual ~CardList();

private:

	static CardList* Instance;
};

