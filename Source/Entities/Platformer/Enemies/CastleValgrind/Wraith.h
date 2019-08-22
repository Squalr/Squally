#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Wraith : public PlatformerEnemy
{
public:
	static Wraith* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyWraith;

private:
	typedef PlatformerEnemy super;
	Wraith(cocos2d::ValueMap& properties);
	~Wraith();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
