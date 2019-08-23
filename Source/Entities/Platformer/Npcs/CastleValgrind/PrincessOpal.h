#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;
class LocalizedString;

class PrincessOpal : public PlatformerFriendly
{
public:
	static PrincessOpal* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyPrincessOpal;

private:
	typedef PlatformerFriendly super;
	PrincessOpal(cocos2d::ValueMap& properties);
	~PrincessOpal();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
