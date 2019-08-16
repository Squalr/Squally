#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Shaman : public PlatformerEnemy
{
public:
	static Shaman* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyShaman;

private:
	typedef PlatformerEnemy super;
	Shaman(cocos2d::ValueMap& properties);
	~Shaman();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
