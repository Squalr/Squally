#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class DemonGrunt : public PlatformerEnemy
{
public:
	static DemonGrunt* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyDemonGrunt;

private:
	typedef PlatformerEnemy super;
	DemonGrunt(cocos2d::ValueMap& initProperties);
	~DemonGrunt();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
