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
	std::string getBattleTag();
	std::string getDropPool();
	void setDropPool(std::string dropPool);

	static const std::string MapKeyBattleMap;
	static const std::string MapKeyBattleTag;
	static const std::string MapKeyDropPool;
	static const std::string PlatformerEnemyTag;

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

	void onObjectStateLoaded() override;

	std::string battleMapResource;
	std::string battleMapTag;
	std::string dropPool;

private:
	typedef PlatformerEntity super;
};
