#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class AnubisPup : public PlatformerEnemy
{
public:
	static AnubisPup* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyAnubisPup;

private:
	typedef PlatformerEnemy super;
	AnubisPup(cocos2d::ValueMap& properties);
	~AnubisPup();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
