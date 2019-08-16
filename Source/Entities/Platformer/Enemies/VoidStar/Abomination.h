#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Abomination : public PlatformerEnemy
{
public:
	static Abomination* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyAbomination;

private:
	typedef PlatformerEnemy super;
	Abomination(cocos2d::ValueMap& properties);
	~Abomination();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
