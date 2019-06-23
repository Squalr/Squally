#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Krampus : public PlatformerEnemy
{
public:
	static Krampus* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyKrampus;

private:
	typedef PlatformerEnemy super;
	Krampus(cocos2d::ValueMap& initProperties);
	~Krampus();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
