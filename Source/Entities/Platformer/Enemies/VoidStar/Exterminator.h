#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Exterminator : public PlatformerEnemy
{
public:
	static Exterminator* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyExterminator;

private:
	typedef PlatformerEnemy super;
	Exterminator(cocos2d::ValueMap& initProperties);
	~Exterminator();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
