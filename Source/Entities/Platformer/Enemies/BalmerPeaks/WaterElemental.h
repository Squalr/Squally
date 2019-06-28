#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class WaterElemental : public PlatformerEnemy
{
public:
	static WaterElemental* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyWaterElemental;

private:
	typedef PlatformerEnemy super;
	WaterElemental(cocos2d::ValueMap& initProperties);
	~WaterElemental();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
