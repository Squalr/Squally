#pragma once

#include "Objects/Platformer/Interactables/Chests/ChestBase.h"

class MinMaxPool;

// A lootable book that gives the arcane spellbook instead of items.
class ArcaneBook : public ChestBase
{
public:
	static ArcaneBook* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ArcaneBook(cocos2d::ValueMap& properties);
	virtual ~ArcaneBook();

	void onEnter() override;
	bool tryOpen() override;

private:
	typedef ChestBase super;
};
