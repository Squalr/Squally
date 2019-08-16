#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Cyclops : public PlatformerEnemy
{
public:
	static Cyclops* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyCyclops;

private:
	typedef PlatformerEnemy super;
	Cyclops(cocos2d::ValueMap& properties);
	~Cyclops();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
