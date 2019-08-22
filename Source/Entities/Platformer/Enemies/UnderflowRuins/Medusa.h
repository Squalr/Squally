#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Medusa : public PlatformerEnemy
{
public:
	static Medusa* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyMedusa;

private:
	typedef PlatformerEnemy super;
	Medusa(cocos2d::ValueMap& properties);
	~Medusa();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
