#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;
class LocalizedString;

class PrincessDawn : public PlatformerFriendly
{
public:
	static PrincessDawn* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyPrincessDawn;

private:
	typedef PlatformerFriendly super;
	PrincessDawn(cocos2d::ValueMap& properties);
	~PrincessDawn();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
