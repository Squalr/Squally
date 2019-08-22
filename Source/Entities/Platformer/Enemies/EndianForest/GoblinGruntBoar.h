#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class GoblinGruntBoar : public PlatformerEnemy
{
public:
	static GoblinGruntBoar* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGoblinGruntBoar;

private:
	typedef PlatformerEnemy super;
	GoblinGruntBoar(cocos2d::ValueMap& properties);
	~GoblinGruntBoar();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
