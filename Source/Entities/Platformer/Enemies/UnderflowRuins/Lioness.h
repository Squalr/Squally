#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Lioness : public PlatformerEnemy
{
public:
	static Lioness* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyLioness;

private:
	typedef PlatformerEnemy super;
	Lioness(cocos2d::ValueMap& properties);
	~Lioness();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
