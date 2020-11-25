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
class HelpMenu;
class HexusCard;
class HexusFilter;
class ItemMenu;
class Inventory;
template <class T>
class LazyNode;
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
	HelpMenu* buildHelpMenu();

	cocos2d::Sprite* cardsWindow;
	LocalizedLabel* cardsLabel;
	ItemMenu* equippedCardsMenu;
	ItemMenu* unequippedCardsMenu;
	ClickableTextNode* returnButton;
	ClickableNode* closeButton;
	cocos2d::LayerColor* backdrop;
	LazyNode<HelpMenu>* helpMenu;

	EquipmentInventory* equipmentInventory;
	Inventory* inventory;
	HexusFilter* hexusFilter;

	std::function<void()> returnClickCallback;
	bool equipmentChanged;

	static const int MinHexusCards;
	static const int MaxHexusCards;
};
