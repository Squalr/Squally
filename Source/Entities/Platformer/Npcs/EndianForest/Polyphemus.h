#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Polyphemus : public PlatformerFriendly
{
public:
	static Polyphemus* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyPolyphemus;

private:
	typedef PlatformerFriendly super;
	Polyphemus(cocos2d::ValueMap& properties);
	~Polyphemus();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
