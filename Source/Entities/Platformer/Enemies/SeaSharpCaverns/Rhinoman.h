#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Rhinoman : public PlatformerEnemy
{
public:
	static Rhinoman* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyRhinoman;

private:
	typedef PlatformerEnemy super;
	Rhinoman(cocos2d::ValueMap& properties);
	~Rhinoman();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
