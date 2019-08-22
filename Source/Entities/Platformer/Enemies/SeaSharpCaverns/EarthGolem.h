#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class EarthGolem : public PlatformerEnemy
{
public:
	static EarthGolem* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyEarthGolem;

private:
	typedef PlatformerEnemy super;
	EarthGolem(cocos2d::ValueMap& properties);
	~EarthGolem();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
