#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class DemonSwordsman : public PlatformerEnemy
{
public:
	static DemonSwordsman* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyDemonSwordsman;

private:
	typedef PlatformerEnemy super;
	DemonSwordsman(cocos2d::ValueMap& properties);
	~DemonSwordsman();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
