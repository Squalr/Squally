#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Ajax : public PlatformerFriendly
{
public:
	static Ajax* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyAjax;

private:
	typedef PlatformerFriendly super;
	Ajax(cocos2d::ValueMap& properties);
	~Ajax();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
