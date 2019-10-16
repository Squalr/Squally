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
	static ItemEntry* create(LocalizedString* text, std::string spriteResource = "");

	void setToggleCallback(std::function<void()> onToggle);
	std::function<void()> getToggleCallback();

protected:
	ItemEntry(LocalizedString* text, std::string spriteResource);
	~ItemEntry();

private:
	typedef MenuEntry super;

	Item* associatedItem;
	
	std::function<void()> onToggle;
};
