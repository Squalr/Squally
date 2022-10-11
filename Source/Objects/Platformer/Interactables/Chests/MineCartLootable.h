#pragma once

#include "Objects/Platformer/Interactables/Chests/ChestBase.h"

class MineCartLootable : public ChestBase
{
public:
	static MineCartLootable* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	MineCartLootable(cocos2d::ValueMap& properties);
	virtual ~MineCartLootable();

private:
	typedef ChestBase super;
	
	enum class CartColor
	{
		Brown,
		Blue
	};
	
	enum class Fill
	{
		None,
		Coal,
		Gold,
		Diamond
	};

	void parseColor();
	void parseFill();
	cocos2d::Node* buildCart(bool withFill);

	CartColor cartColor = CartColor::Brown;
	Fill cartFill = Fill::None;

	static const std::string PropertyFill;
	static const std::string PropertyColor;
};
