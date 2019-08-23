#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;
class LocalizedString;

class PrincessMittens : public PlatformerFriendly
{
public:
	static PrincessMittens* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyPrincessMittens;

private:
	typedef PlatformerFriendly super;
	PrincessMittens(cocos2d::ValueMap& properties);
	~PrincessMittens();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
