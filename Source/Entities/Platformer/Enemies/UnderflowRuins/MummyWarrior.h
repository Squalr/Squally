#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class MummyWarrior : public PlatformerEnemy
{
public:
	static MummyWarrior* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyMummyWarrior;

private:
	typedef PlatformerEnemy super;
	MummyWarrior(cocos2d::ValueMap& initProperties);
	~MummyWarrior();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
