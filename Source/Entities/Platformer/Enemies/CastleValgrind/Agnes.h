#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Agnes : public PlatformerEnemy
{
public:
	static Agnes* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyAgnes;

private:
	typedef PlatformerEnemy super;
	Agnes(cocos2d::ValueMap& properties);
	~Agnes();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
