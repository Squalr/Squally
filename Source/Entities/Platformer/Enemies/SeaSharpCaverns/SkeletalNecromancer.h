#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class SkeletalNecromancer : public PlatformerEnemy
{
public:
	static SkeletalNecromancer* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeySkeletalNecromancer;

private:
	typedef PlatformerEnemy super;
	SkeletalNecromancer(cocos2d::ValueMap& properties);
	~SkeletalNecromancer();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
