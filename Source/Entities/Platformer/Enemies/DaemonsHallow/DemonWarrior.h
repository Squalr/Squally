#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class DemonWarrior : public PlatformerEnemy
{
public:
	static DemonWarrior* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyDemonWarrior;

private:
	typedef PlatformerEnemy super;
	DemonWarrior(cocos2d::ValueMap& initProperties);
	~DemonWarrior();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
