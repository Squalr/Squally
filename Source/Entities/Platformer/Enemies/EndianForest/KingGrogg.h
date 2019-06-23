#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class KingGrogg : public PlatformerEnemy
{
public:
	static KingGrogg* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyKingGrogg;

private:
	typedef PlatformerEnemy super;
	KingGrogg(cocos2d::ValueMap& initProperties);
	~KingGrogg();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
