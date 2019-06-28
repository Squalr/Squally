#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class LionMan : public PlatformerEnemy
{
public:
	static LionMan* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyLionMan;

private:
	typedef PlatformerEnemy super;
	LionMan(cocos2d::ValueMap& initProperties);
	~LionMan();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
