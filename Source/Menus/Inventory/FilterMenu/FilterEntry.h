#pragma once

#include "Menus/Inventory/MenuEntry.h"

namespace cocos2d
{
	class Sprite;
}

class Item;
class LocalizedLabel;
class LocalizedString;

class FilterEntry : public MenuEntry
{
public:
	virtual std::vector<Item*> filter(std::vector<Item*> itemList) = 0;

protected:
	FilterEntry(LocalizedString* text, std::string spriteResource);
	virtual ~FilterEntry();

private:
	typedef MenuEntry super;
};
