#pragma once

#include "Entities/Platformer/PlatformerEntity.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class Inventory;

// Base class for enemies
class PlatformerEnemy : public PlatformerEntity
{
public:
	std::string getBattleMapResource();
	std::string getBattleBehavior();
	Inventory* getDropInventory();

	static const std::string MapKeyBattleAttachedBehavior;
	static const std::string MapKeyBattleMap;

protected:
	PlatformerEnemy(cocos2d::ValueMap& properties,
		std::string entityName,
		std::string scmlResource,
		std::string emblemResource,
		cocos2d::Size size,
		float scale,
		cocos2d::Vec2 collisionOffset,
		float hoverHeight = 0.0f);
	virtual ~PlatformerEnemy();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onObjectStateLoaded() override;
	std::tuple<std::string, float> createDrop(std::string itemKey, float probability);

	std::string battleMapResource;
	std::string battleBehavior;
	std::vector<std::tuple<std::string, float>> dropTable;
	std::tuple<int, int> iouTable;

private:
	typedef PlatformerEntity super;

	Inventory* dropInventory;

	void buildDropInventory();
	void buildIOUDrop();
};
