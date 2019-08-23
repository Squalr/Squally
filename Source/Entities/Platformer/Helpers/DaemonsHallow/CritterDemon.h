#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;
class LocalizedString;

class CritterDemon : public PlatformerFriendly
{
public:
	static CritterDemon* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyCritterDemon;

private:
	typedef PlatformerFriendly super;
	CritterDemon(cocos2d::ValueMap& properties);
	~CritterDemon();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
