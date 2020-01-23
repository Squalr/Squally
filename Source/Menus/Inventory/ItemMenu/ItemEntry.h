#pragma once

#include "Menus/Inventory/MenuEntry.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class Item;

class ItemEntry : public MenuEntry
{
public:
	static ItemEntry* create(Item* associatedItem, LocalizedString* text, std::string spriteResource = "");

	void setToggleCallback(std::function<void()> onToggle);
	std::function<void()> getToggleCallback();
	Item* getAssociatedItem();
	int getStackSize();
	void setStackSize(int stackSize);

protected:
	ItemEntry(Item* associatedItem, LocalizedString* text, std::string spriteResource);
	virtual ~ItemEntry();

private:
	typedef MenuEntry super;

	ConstantString* stackString;
	Item* associatedItem;
	int stackSize;
	
	std::function<void()> onToggle;
};
