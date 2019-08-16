#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class SnowFiend : public PlatformerEnemy
{
public:
	static SnowFiend* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeySnowFiend;

private:
	typedef PlatformerEnemy super;
	SnowFiend(cocos2d::ValueMap& properties);
	~SnowFiend();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
