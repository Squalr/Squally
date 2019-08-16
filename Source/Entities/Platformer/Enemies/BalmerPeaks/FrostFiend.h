#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class FrostFiend : public PlatformerEnemy
{
public:
	static FrostFiend* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyFrostFiend;

private:
	typedef PlatformerEnemy super;
	FrostFiend(cocos2d::ValueMap& properties);
	~FrostFiend();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
