#pragma once

#include "Menus/Inventory/MenuEntry.h"

namespace cocos2d
{
	class Sprite;
}

class Item;

class ItemEntry : public MenuEntry
{
public:
	static ItemEntry* create(Item* associatedItem, LocalizedString* text, std::string spriteResource = "");

	void setToggleCallback(std::function<void()> onToggle);
	std::function<void()> getToggleCallback();
	Item* getAssociatedItem();

protected:
	ItemEntry(Item* associatedItem, LocalizedString* text, std::string spriteResource);
	virtual ~ItemEntry();

private:
	typedef MenuEntry super;

	Item* associatedItem;
	
	std::function<void()> onToggle;
};
