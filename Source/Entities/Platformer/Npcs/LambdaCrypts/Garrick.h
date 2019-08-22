#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Garrick : public PlatformerFriendly
{
public:
	static Garrick* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGarrick;

private:
	typedef PlatformerFriendly super;
	Garrick(cocos2d::ValueMap& properties);
	~Garrick();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
