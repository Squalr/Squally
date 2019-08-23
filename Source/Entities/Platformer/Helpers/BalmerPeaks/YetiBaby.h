#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;
class LocalizedString;

class YetiBaby : public PlatformerFriendly
{
public:
	static YetiBaby* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyYetiBaby;

private:
	typedef PlatformerFriendly super;
	YetiBaby(cocos2d::ValueMap& properties);
	~YetiBaby();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
