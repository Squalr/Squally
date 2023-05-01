#pragma once

#include "cocos/base/ccTypes.h"

#include "Entities/Platformer/PlatformerEntity.h"

// Base class for enemies
class PlatformerEnemy : public PlatformerEntity
{
public:
	std::string getBattleMapResource();
	std::string getBattleTag();
	std::string getDropPool();
	void setDropPool(std::string dropPool);

	static const std::string PropertyBattleMap;
	static const std::string PropertyBattleTag;
	static const std::string PropertyDropPool;
	static const std::string PlatformerEnemyTag;

protected:
	PlatformerEnemy(cocos2d::ValueMap& properties,
		std::string entityName,
		std::string scmlResource,
		std::string emblemResource,
		cocos2d::CSize size,
		float scale,
		float hoverHeight = 0.0f);
	virtual ~PlatformerEnemy();

	std::string battleMapResource;
	std::string battleMapTag;
	std::string dropPool;

private:
	typedef PlatformerEntity super;
};
