#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Assassin : public PlatformerEnemy
{
public:
	static Assassin* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyAssassin;

private:
	typedef PlatformerEnemy super;
	Assassin(cocos2d::ValueMap& properties);
	~Assassin();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
