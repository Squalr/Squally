#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class DemonRogue : public PlatformerEnemy
{
public:
	static DemonRogue* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyDemonRogue;

private:
	typedef PlatformerEnemy super;
	DemonRogue(cocos2d::ValueMap& properties);
	~DemonRogue();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
