#pragma once

#include "Entities/Platformer/PlatformerEntity.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class ClickableNode;

// Base class for enemies
class PlatformerEnemy : public PlatformerEntity
{
public:
	std::string getBattleMapResource();
	std::vector<std::string> getBattleMapArgs();
	std::vector<std::string> getCombatEntityList();

	static const std::string SaveKeyIsDead;
	static const std::string MapKeyBattleArgs;
	static const std::string MapKeyBattleMap;
	static const std::string MapKeyAlly1;
	static const std::string MapKeyAlly2;
	static const std::string MapKeyAlly3;

protected:
	PlatformerEnemy(cocos2d::ValueMap& properties,
		std::string scmlResource,
		std::string emblemResource,
		PlatformerCollisionType collisionType,
		cocos2d::Size size,
		float scale,
		cocos2d::Vec2 collisionOffset,
		int baseHealth,
		int baseSpecial,
		cocos2d::Size movementCollisionSize = cocos2d::Size::ZERO,
		float ghettoGroundCollisionFix = 0.0f);
	virtual ~PlatformerEnemy();

	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onObjectStateLoaded() override;
	std::tuple<std::string, float> createDrop(std::string itemKey, float probability);

	std::string battleMapResource;
	std::vector<std::string> battleMapArgs;
	std::vector<std::string> combatEntityList;
	std::vector<std::tuple<std::string, float>> dropTable = std::vector<std::tuple<std::string, float>>();

private:
	typedef PlatformerEntity super;

	void buildDropInventory();

	ClickableNode* resurrectButton;
	ClickableNode* killButton;
};
