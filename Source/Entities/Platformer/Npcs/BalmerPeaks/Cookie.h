#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Cookie : public PlatformerFriendly
{
public:
	static Cookie* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyCookie;

private:
	typedef PlatformerFriendly super;
	Cookie(cocos2d::ValueMap& properties);
	~Cookie();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
