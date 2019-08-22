#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Thatcher : public PlatformerFriendly
{
public:
	static Thatcher* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyThatcher;

private:
	typedef PlatformerFriendly super;
	Thatcher(cocos2d::ValueMap& properties);
	~Thatcher();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
