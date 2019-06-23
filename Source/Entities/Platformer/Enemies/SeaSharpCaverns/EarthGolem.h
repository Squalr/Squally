#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class EarthGolem : public PlatformerEnemy
{
public:
	static EarthGolem* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyEarthGolem;

private:
	typedef PlatformerEnemy super;
	EarthGolem(cocos2d::ValueMap& initProperties);
	~EarthGolem();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
