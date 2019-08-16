#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class SkeletalKnight : public PlatformerEnemy
{
public:
	static SkeletalKnight* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeySkeletalKnight;

private:
	typedef PlatformerEnemy super;
	SkeletalKnight(cocos2d::ValueMap& properties);
	~SkeletalKnight();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
