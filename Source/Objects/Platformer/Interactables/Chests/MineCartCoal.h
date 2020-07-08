#pragma once

#include "Objects/Platformer/Interactables/Chests/ChestBase.h"

class MineCartCoal : public ChestBase
{
public:
	static MineCartCoal* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	MineCartCoal(cocos2d::ValueMap& properties);
	virtual ~MineCartCoal();

private:
	typedef ChestBase super;
	
	enum class CartColor
	{
		Brown,
		Blue
	};

	cocos2d::Node* buildCart(bool withFill);

	CartColor cartColor;

	static const std::string PropertyColor;
};
