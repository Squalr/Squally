#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class SkeletalBaron : public PlatformerEnemy
{
public:
	static SkeletalBaron* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeySkeletalBaron;

private:
	typedef PlatformerEnemy super;
	SkeletalBaron(cocos2d::ValueMap& properties);
	~SkeletalBaron();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
