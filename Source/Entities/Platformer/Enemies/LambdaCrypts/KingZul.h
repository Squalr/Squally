#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class KingZul : public PlatformerEnemy
{
public:
	static KingZul* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyKingZul;

private:
	typedef PlatformerEnemy super;
	KingZul(cocos2d::ValueMap& properties);
	~KingZul();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
