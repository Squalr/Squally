#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Cyrogen : public PlatformerEnemy
{
public:
	static Cyrogen* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyCyrogen;

private:
	typedef PlatformerEnemy super;
	Cyrogen(cocos2d::ValueMap& initProperties);
	~Cyrogen();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
