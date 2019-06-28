#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class AnubisWarrior : public PlatformerEnemy
{
public:
	static AnubisWarrior* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyAnubisWarrior;

private:
	typedef PlatformerEnemy super;
	AnubisWarrior(cocos2d::ValueMap& initProperties);
	~AnubisWarrior();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
