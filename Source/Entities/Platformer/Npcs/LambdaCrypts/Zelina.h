#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Zelina : public PlatformerFriendly
{
public:
	static Zelina* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyZelina;

private:
	typedef PlatformerFriendly super;
	Zelina(cocos2d::ValueMap& properties);
	~Zelina();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
