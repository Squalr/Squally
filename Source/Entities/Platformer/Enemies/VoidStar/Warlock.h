#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Warlock : public PlatformerEnemy
{
public:
	static Warlock* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyWarlock;

private:
	typedef PlatformerEnemy super;
	Warlock(cocos2d::ValueMap& properties);
	~Warlock();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
