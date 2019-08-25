#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;
class LocalizedString;

class Guano : public PlatformerFriendly
{
public:
	static Guano* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGuano;

private:
	typedef PlatformerFriendly super;
	Guano(cocos2d::ValueMap& properties);
	~Guano();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
