#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class DemonWarrior : public PlatformerEnemy
{
public:
	static DemonWarrior* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyDemonWarrior;

private:
	typedef PlatformerEnemy super;
	DemonWarrior(cocos2d::ValueMap& properties);
	~DemonWarrior();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
