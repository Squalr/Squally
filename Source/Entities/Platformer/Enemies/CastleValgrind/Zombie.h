#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Zombie : public PlatformerEnemy
{
public:
	static Zombie* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyZombie;

private:
	typedef PlatformerEnemy super;
	Zombie(cocos2d::ValueMap& properties);
	~Zombie();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
