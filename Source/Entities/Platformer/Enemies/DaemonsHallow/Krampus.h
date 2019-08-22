#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Krampus : public PlatformerEnemy
{
public:
	static Krampus* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyKrampus;

private:
	typedef PlatformerEnemy super;
	Krampus(cocos2d::ValueMap& properties);
	~Krampus();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
