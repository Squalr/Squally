#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class RecipePoolEF : public MinMaxPool
{
public:
	static RecipePoolEF* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	RecipePoolEF(cocos2d::ValueMap& properties);
	virtual ~RecipePoolEF();

private:
	typedef MinMaxPool super;
};
