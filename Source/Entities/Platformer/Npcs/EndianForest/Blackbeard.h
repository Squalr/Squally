#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;
class LocalizedString;

class Blackbeard : public PlatformerFriendly
{
public:
	static Blackbeard* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyBlackbeard;

private:
	typedef PlatformerFriendly super;
	Blackbeard(cocos2d::ValueMap& properties);
	~Blackbeard();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
