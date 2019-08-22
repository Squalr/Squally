#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class ReanimatedFighter : public PlatformerEnemy
{
public:
	static ReanimatedFighter* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyReanimatedFighter;

private:
	typedef PlatformerEnemy super;
	ReanimatedFighter(cocos2d::ValueMap& properties);
	~ReanimatedFighter();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
