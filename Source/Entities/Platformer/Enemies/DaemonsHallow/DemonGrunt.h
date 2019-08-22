#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class DemonGrunt : public PlatformerEnemy
{
public:
	static DemonGrunt* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyDemonGrunt;

private:
	typedef PlatformerEnemy super;
	DemonGrunt(cocos2d::ValueMap& properties);
	~DemonGrunt();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
