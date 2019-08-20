#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Cryogen : public PlatformerEnemy
{
public:
	static Cryogen* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyCryogen;

private:
	typedef PlatformerEnemy super;
	Cryogen(cocos2d::ValueMap& properties);
	~Cryogen();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
