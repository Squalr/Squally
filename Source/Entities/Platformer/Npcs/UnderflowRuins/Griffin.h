#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Griffin : public PlatformerFriendly
{
public:
	static Griffin* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGriffin;

private:
	typedef PlatformerFriendly super;
	Griffin(cocos2d::ValueMap& properties);
	~Griffin();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
