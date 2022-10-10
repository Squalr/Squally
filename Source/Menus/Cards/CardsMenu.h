#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class CardData;
class ClickableNode;
class ClickableTextNode;
class EquipmentInventory;
class HexusCard;
class HexusFilter;
class ItemMenu;
class Inventory;
template <class T> class LazyNode;
class LocalizedLabel;

class CardsMenu : public SmartNode
{
public:
	static CardsMenu* create();

	void open();
	void setReturnClickCallback(std::function<void()> returnClickCallback);

protected:
	CardsMenu();
	virtual ~CardsMenu();

private:
	typedef SmartNode super;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void populateItemList();
	void equipHexusCard(HexusCard* card);
	void unequipHexusCard(HexusCard* card);
	void showHelpMenu(CardData* cardData);
	void close();

	cocos2d::Sprite* cardsWindow = nullptr;
	LocalizedLabel* cardsLabel = nullptr;
	ItemMenu* equippedCardsMenu = nullptr;
	ItemMenu* unequippedCardsMenu = nullptr;
	ClickableTextNode* returnButton = nullptr;
	ClickableNode* closeButton = nullptr;
	cocos2d::LayerColor* backdrop = nullptr;

	EquipmentInventory* equipmentInventory = nullptr;
	Inventory* inventory = nullptr;
	HexusFilter* hexusFilter = nullptr;

	std::function<void()> returnClickCallback = nullptr;
	bool equipmentChanged = false;

	static const int MinHexusCards;
	static const int MaxHexusCards;
};
