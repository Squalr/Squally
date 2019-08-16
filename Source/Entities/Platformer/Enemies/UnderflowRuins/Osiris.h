#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Osiris : public PlatformerEnemy
{
public:
	static Osiris* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyOsiris;

private:
	typedef PlatformerEnemy super;
	Osiris(cocos2d::ValueMap& properties);
	~Osiris();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
