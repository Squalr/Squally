#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class MummyPriest : public PlatformerEnemy
{
public:
	static MummyPriest* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyMummyPriest;

private:
	typedef PlatformerEnemy super;
	MummyPriest(cocos2d::ValueMap& initProperties);
	~MummyPriest();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
