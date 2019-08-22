#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class LavaGolem : public PlatformerEnemy
{
public:
	static LavaGolem* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyLavaGolem;

private:
	typedef PlatformerEnemy super;
	LavaGolem(cocos2d::ValueMap& properties);
	~LavaGolem();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
