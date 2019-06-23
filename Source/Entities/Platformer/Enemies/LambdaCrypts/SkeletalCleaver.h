#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class SkeletalCleaver : public PlatformerEnemy
{
public:
	static SkeletalCleaver* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeySkeletalCleaver;

private:
	typedef PlatformerEnemy super;
	SkeletalCleaver(cocos2d::ValueMap& initProperties);
	~SkeletalCleaver();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
