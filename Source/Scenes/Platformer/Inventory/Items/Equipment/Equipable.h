#pragma once

#include "Engine/Inventory/Item.h"

class LocalizedString;

class Equipable : public Item
{
public:

protected:
	Equipable(LocalizedString* name, std::string iconResource);
	virtual ~Equipable();

	virtual cocos2d::Vec2 getDisplayOffset();

private:
	typedef Item super;
};
