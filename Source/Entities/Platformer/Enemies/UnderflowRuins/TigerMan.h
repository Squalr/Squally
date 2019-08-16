#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class TigerMan : public PlatformerEnemy
{
public:
	static TigerMan* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyTigerMan;

private:
	typedef PlatformerEnemy super;
	TigerMan(cocos2d::ValueMap& properties);
	~TigerMan();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
