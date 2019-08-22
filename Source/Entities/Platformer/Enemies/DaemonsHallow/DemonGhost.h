#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class DemonGhost : public PlatformerEnemy
{
public:
	static DemonGhost* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyDemonGhost;

private:
	typedef PlatformerEnemy super;
	DemonGhost(cocos2d::ValueMap& properties);
	~DemonGhost();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
