#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Gorilla : public PlatformerEnemy
{
public:
	static Gorilla* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGorilla;

private:
	typedef PlatformerEnemy super;
	Gorilla(cocos2d::ValueMap& properties);
	~Gorilla();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
