#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Rogas : public PlatformerFriendly
{
public:
	static Rogas* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyRogas;

private:
	typedef PlatformerFriendly super;
	Rogas(cocos2d::ValueMap& properties);
	~Rogas();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
