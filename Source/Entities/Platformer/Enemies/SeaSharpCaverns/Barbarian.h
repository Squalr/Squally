#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Barbarian : public PlatformerEnemy
{
public:
	static Barbarian* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyBarbarian;

private:
	typedef PlatformerEnemy super;
	Barbarian(cocos2d::ValueMap& properties);
	~Barbarian();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
