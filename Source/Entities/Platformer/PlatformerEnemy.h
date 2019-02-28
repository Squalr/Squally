#pragma once

#include "Entities/Platformer/PlatformerEntity.h"

class ClickableNode;

// Base class for enemies
class PlatformerEnemy : public PlatformerEntity
{
public:
	std::string getBattleMapResource();
	std::vector<std::string> getCombatEntityList();

	static const std::string SaveKeyIsDead;
	static const std::string MapKeyBattleMap;
	static const std::string MapKeyAlly1;
	static const std::string MapKeyAlly2;
	static const std::string MapKeyAlly3;

protected:
	PlatformerEnemy(cocos2d::ValueMap& initProperties,
		std::string scmlResource,
		std::string emblemResource,
		PlatformerCollisionType collisionType,
		cocos2d::Size size,
		float scale,
		cocos2d::Vec2 collisionOffset,
		int baseHealth,
		int baseSpecial);
	virtual ~PlatformerEnemy();

	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onObjectStateLoaded() override;

	std::string battleMapResource;
	std::vector<std::string> combatEntityList;
	std::map<std::string, float> dropTable = std::map<std::string, float>();

private:
	typedef PlatformerEntity super;

	void buildDropInventory();

	ClickableNode* resurrectButton;
	ClickableNode* killButton;
};
