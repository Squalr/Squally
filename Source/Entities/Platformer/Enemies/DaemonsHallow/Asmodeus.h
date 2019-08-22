#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Asmodeus : public PlatformerEnemy
{
public:
	static Asmodeus* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyAsmodeus;

private:
	typedef PlatformerEnemy super;
	Asmodeus(cocos2d::ValueMap& properties);
	~Asmodeus();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
