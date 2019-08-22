#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Mystic : public PlatformerEnemy
{
public:
	static Mystic* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyMystic;

private:
	typedef PlatformerEnemy super;
	Mystic(cocos2d::ValueMap& properties);
	~Mystic();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
